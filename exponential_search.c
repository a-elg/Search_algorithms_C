/*****************************************************************
(C)Septiembre 2021

EQUIPO: Ponys Salvajes
INTEGRANTES DEL EQUIPO: 
    López Gracia Angel Emmanuel 
    López Hernández Lissete 
    Martínez Martínez Fernando 
    Martínez Ortiz Fabiola Yahel	
  VERSIÓN: 1.0
DESCRIPCIÓN: Implementación del algoritmo de búsqueda exponencial. Mide el tiempo de ejecución del algoritmo. 
			Se toman los valores de entrada del archivo .txt con los 10 millones de números.

CURSO: Análisis de algoritmos
    COMPILACIÓN: "gcc [nombre_del_programa].c tiempo.x  -o main” 
    EJECUCIÓN: "./main n" (Linux y MAC OS)
*****************************************************************/

 
//LIBRERIAS INCLUIDAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
//*****************************************************************

//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)
/*prototipo para la función que implementa el algoritmo de búsqueda exponencial*/
int exponential_search(int arr[], int n, int x);
/*prototipo para la función que implementa el algoritmo de búsqueda binaria*/
int binary_search(int A[], int l, int r, int x);
/*prototipo para la funcion que obtiene el minimo de dos numeros*/
int min(int a, int b);

//*****************************************************************

//PROGRAMA PRINCIPAL 
int main (int argc, char* argv[]){	
	int *A;
	int x = 0;
    int tam, result;
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
	//*****************************************************************
	
	//INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO	
	uswtime(&utime0, &stime0, &wtime0);

	//ALGORITMO	
	//Llamada a la función del algoritmo
    result = exponential_search(A, tam, x);

	//EVALUAR LOS TIEMPOS DE EJECUCIÓN 
	uswtime(&utime1, &stime1, &wtime1);

	/*Cálculo del tiempo de ejecución del programa
	printf("\n");
	printf("real (Tiempo total)  %.10f s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10f s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10f s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	
	//Mostrar los tiempos en formato exponecial
	printf("\n");
	printf("real (Tiempo total)  %.10e s\n",  wtime1 - wtime0);
	printf("user (Tiempo de procesamiento en CPU) %.10e s\n",  utime1 - utime0);
	printf("sys (Tiempo en acciónes de E/S)  %.10e s\n",  stime1 - stime0);
	printf("CPU/Wall   %.10f %% \n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	printf("\n");
	*/

	//FORMATO PARA OBTENER TIEMPO DE EJECUCIÓN 
	printf("Insrt %15.10e  %21.10e %21.10e %21.10f%% \n", wtime1 - wtime0,utime1 - utime0,stime1 - stime0,100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
	//Prueba del resultado
	printf("Indice de %d: %d", x, result);
	//Finaliza programa 
	exit (0);	
}

//DEFINICIÓN DE FUNCIONES 
//************************************************************************

/*FUNCIÓN QUE IMPLEMENTA EL ALGORITMO DE BÚSQUEDA EXPOENCIAL*/
/* Recibe: Un arreglo A de los elementos, una varible n que indica el tamaño del arreglo y la variable x a buscar*/
/* Devuelve: El indice donde se encuentra el elemento, -1 si no se encuentra*/ 
/* Descripción:  */
int exponential_search(int A[], int n, int x){
	if(A[0] == x) //Se compara si el elemento esta en la primera posicion
		return 0;
	
	int i = 1;
	while(i<n && A[i] <=x) //Se busca el intervalo (de forma exponencial) para aplicar la busqueda binaria
		i = i*2;

	return binary_search(A, i/2, min(i, n-1), x); //Aplica busqueda binaria en el intervalo
}

/*FUNCIÓN QUE IMPLEMENTA EL ALGORITMO DE BÚSQUEDA BINARIA*/
int binary_search(int A[], int l, int r, int x){
    // Mientras el inicio sea menor o igual al final del arreglo
    while (l <= r) {
        int m = l + (r - l) / 2;
  
        // Valida si el número esta presente a la mitad
        if (A[m] == x)
            return m;
  
        // Compara si el número es mayor al valor en la mitad. Ignora mitad izquierda
        if (A[m] < x)
            l = m + 1;
  
        // Si es menor, ignora la mitad derecha.
        else
            r = m - 1;
    }
    // Regresa -1 en caso de no haber encontrado el número 
    return -1;
}

/*FUNCIÓN QUE OBTIENE EL MINIMO DE DOS NUMEROS*/
int min(int a, int b){
	if(a < b)
		return a;
	else 
		return b;
}