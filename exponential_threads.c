/*****************************************************************
(C)Septiembre 2021
EQUIPO: Ponys Salvajes
INTEGRANTES DEL EQUIPO: 
    López Gracia Angel Emmanuel 
    López Hernández Lissete 
    Martínez Martínez Fernando 
    Martínez Ortiz Fabiola Yahel	
  VERSIÓN: 1.0
DESCRIPCIÓN: Implementación del algoritmo de búsqueda exponencial con hilos. Mide el tiempo de ejecución del algoritmo. 
			Se toman los valores de entrada del archivo .txt con los 10 millones de números.

CURSO: Análisis de algoritmos
    COMPILACIÓN: "gcc exponential_threads.c tiempo.o -pthread -o exponential_threads” 
    EJECUCIÓN: "./exponential_threads tamaño numero < entradaDeNumeros.txt" (Linux y MAC OS)
*****************************************************************/

 
//LIBRERIAS INCLUIDAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
#include <math.h>
/*Librerías para el manejo de hilos*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#define THREADS 2 //Numero de hilos (Cantidad divisible entre tamaño n)
//*****************************************************************

//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)
/*prototipo para la función que implementa el algoritmo de búsqueda exponencial para hilos*/
void* exponential_search_thread(void * data);
/*prototipo para la función que implementa el algoritmo de búsqueda binaria*/
int binary_search(int A[], int l, int r, int x);
/*prototipo para la funcion que obtiene el minimo de dos numeros*/
int min(int a, int b);

//*****************************************************************

//Estructura para pasar al hilo
typedef struct {
    int * A; //Subarreglo
    int n; //Tamaño del subarreglo
    int x; //Numero a buscar
	int hilo;
} Data;

//*****************************************************************

int result=-1; //Resultado de la busqueda
int idHilo=-1; 

//PROGRAMA PRINCIPAL 
int main (int argc, char* argv[]){	
	int *A;
	int x = 0;
    int tam;
	//Variables para ciclos
	int i, j;
	//Variables para medición de tiempos
	double utime0, stime0, wtime0,utime1, stime1, wtime1; 

	/* RECEPCIÓN Y DECODIFICACIÓN DE ARGUMENTOS */
	//Condicional *if* es verdadera en caso de no introducirse exactamente 3 argumentos (Cadena de ejecución, numero=tamaño y x = )
	if (argc!=3){
		printf("\nIndicar el tamanio del algoritmo, por favor - Ejemplo: [user@equipo]$ %s 100 < numeros10millones.txt\n",argv[0]);
		exit(1);
	} else{ 
		    tam = atoi(argv[1]); //Tomar el segundo argumento como tamaño del algoritmo
            x = atoi(argv[2]); //Tomar el tercer argumento como el número a buscar
    }

	//Asignacion de memoria dinamica para el A de numeros a ordenar
	if ((A = malloc(sizeof(int) * tam)) == NULL)
		perror("La asignacion dinamica no se realizo correctamente");
	//Llenado del arreglo
	for (i = 0; i < tam; i++){
		scanf("%d", &A[i]);
	}	

	printf("Hilos: %d\n", THREADS); //Imprime cuantos hilos se ejecutan

	//*****************************************************************
	
	//INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO	
	uswtime(&utime0, &stime0, &wtime0);

	//ALGORITMO CON HILOS
    pthread_t hilos[THREADS]; //Arreglo con los hilos
	Data datos[THREADS]; //Estructura para cada hilo
    int size = tam/THREADS; //Se obtiene el tamaño de cada subarreglo
    for(i=0; i<THREADS; i++){//Se inician los hilos
		datos[i].A = &A[size*i];
		datos[i].n = size;
		datos[i].x = x;
		datos[i].hilo = i;
		pthread_create(&hilos[i], NULL, exponential_search_thread, (void*) &datos[i]); //Se crea el hilo
    }

	for (i=0; i<THREADS; i++){
		 pthread_join(hilos[i], NULL); //El hilo principal espera que los demás hilos terminen correctamente
	}

	//EVALUAR LOS TIEMPOS DE EJECUCIÓN 
	uswtime(&utime1, &stime1, &wtime1);

	//FORMATO PARA OBTENER TIEMPO DE EJECUCIÓN 
	printf("Insrt %15.10e  %21.10e %21.10e %21.10f%% \n", wtime1 - wtime0,utime1 - utime0,stime1 - stime0,100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	//Prueba del resultado
	printf("Indice de %d: %d\tEncontrado por hilo: %d\n", x, result, idHilo);
	//Finaliza programa 
	exit (0);	
}

//DEFINICIÓN DE FUNCIONES 
//************************************************************************

/*FUNCIÓN QUE IMPLEMENTA EL ALGORITMO DE BÚSQUEDA EXPOENCIAL*/
/* Recibe: Una estrucutura con el arreglo A de los elementos, una varible n que indica el tamaño del arreglo y la variable x a buscar*/
/* Devuelve: void* */ 
/* Descripción:  Este algoritmo busca el elemento en intervalos de tamaño de potencias de 2 y posteriormente aplica busqueda binaria
dicho intervalo*/
void * exponential_search_thread(void * data){
    Data* dato = (Data *) data;
    int* A = dato->A;
    int n = dato->n;
    int x = dato->x;
	int hilo = dato->hilo;
	//printf("Hilo num:%d con id:%ld ha empezado a buscar de %d a %d\n", hilo, pthread_self(),A[0], A[n-1]);

	if(A[0] == x){//Se compara si el elemento esta en la primera posicion
		result = 0+hilo*n;
		idHilo = hilo;
		pthread_exit(NULL);
	} 
	
	int i = 1;
	while(i<n && A[i] <=x) //Se busca el intervalo (de forma exponencial) para aplicar la busqueda binaria
		i = i*2;

	int resultHilo = binary_search(A, i/2, min(i, n-1), x); //Aplica busqueda binaria en el intervalo 
	if(resultHilo != -1){ //Si el hilo encontró el elemento
		result = resultHilo+hilo*n;
		idHilo = hilo;
	}
	pthread_exit(NULL);
}

/*FUNCIÓN QUE IMPLEMENTA EL ALGORITMO DE BÚSQUEDA BINARIA (No hay cambios para hilos)*/
int binary_search(int A[], int l, int r, int x){
    // Mientras el inicio sea menor o igual al final del arreglo
    while (l <= r && result==-1) { //Si result ==-1 no se ha encontrado el elemento
        int m = l + (r - l) / 2;
        // Valida si el número esta presente a la mitad
        if (A[m] == x){
			 return m;
		}
        // Compara si el número es mayor al valor en la mitad. Ignora mitad izquierda
        if (A[m] < x)
            l = m + 1;
        // Si es menor, ignora la mitad derecha.
        else
            r = m - 1;
    }
	return -1; //No se encontró en el subarreglo u otro hilo ya lo encontró
}

/*FUNCIÓN QUE OBTIENE EL MINIMO DE DOS NUMEROS*/
int min(int a, int b){
	if(a < b)
		return a;
	else 
		return b;
}