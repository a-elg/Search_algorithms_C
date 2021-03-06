/*****************************************************************
(C)Septiembre 2021

EQUIPO: Ponys Salvajes
INTEGRANTES DEL EQUIPO: 
    López Gracia Angel Emmanuel 
    López Hernández Lissete 
    Martínez Martínez Fernando 
    Martínez Ortiz Fabiola Yahel	
  VERSIÓN: 1.0
DESCRIPCIÓN: Implementación del algoritmo de búsqueda lineal con hilos. Mide el tiempo de ejecución del algoritmo. 
			Se toman los valores de entrada del archivo .txt con los 10 millones de números.

CURSO: Análisis de algoritmos
    COMPILACIÓN: "gcc [nombre_del_programa].c tiempo.x  -o main” 
    EJECUCIÓN: "./main n" (Linux y MAC OS)
*****************************************************************/

//LIBRERIAS INCLUIDAS
#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"

/*Librerías para el manejo de hilos*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
//*****************************************************************

#define THREADS 8

typedef struct informacion {
    int inicio;
    int fin;
} informacion;

int *A;
int posicion = -1;
int x = 0;

//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)
/*prototipo para la función que implementa el algoritmo de búsqueda lineal*/
int create_threads(int x, int n);
int calc_hilos(int n);
void *thread_process(void *datos);

//PROGRAMA PRINCIPAL
int main(int argc, const char **argv){
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

	//Asignacion de memoria dinamica para el A de numeros
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
    create_threads(x, tam);
    
	//EVALUAR LOS TIEMPOS DE EJECUCIÓN 
	uswtime(&utime1, &stime1, &wtime1);

	//Cálculo del tiempo de ejecución del programa
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
	

	//FORMATO PARA OBTENER TIEMPO DE EJECUCIÓN 
	//printf("Insrt %15.10e  %21.10e %21.10e %21.10f%% \n", wtime1 - wtime0,utime1 - utime0,stime1 - stime0,100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));

	//Finaliza programa 
	exit (0);	

    return 0;
}

//DEFINICIÓN DE FUNCIONES 
//************************************************************************

/*FUNCIÓN QUE IMPLEMENTA EL PROCESO DEL ALGORITMO DE BÚSQUEDA LINEAL*/
/* Recibe: Arreglo de datos tipo apuntador	*/
/* Devuelve: Vacío */
/* Descripción: Busca posición por posición, de inicio a fin, el número a buscar */
void *thread_process(void *datos){
    informacion *info = datos;
    int i = info->inicio;
    while (i < info->fin && posicion == -1) {
        if (A[i] == x) {
            posicion = i;
        }
        i++;
    }
    pthread_exit(0);
}

/* FUNCIÓN QUE CREA LOS HILOS*/
/* Recibe: tamaño del arreglo e índice a buscar	*/
/* Devuelve: Vacío */
/* Descripción: Crea los hilos de acuerdo a la variable global (max threads), 
/* y llama al proceso del algoritmo para cada hilo de acuerdo a la estructura que guarda los índices de inicio a fin */
int create_threads(int x, int n){
    int hilos = calc_hilos(n);
    int actual = n / hilos;
    pthread_t threads[hilos];
    informacion *infos[hilos];
    int status, i, *exit_code;
    /* Asignación de memoria dinámica para las estructuras de cada hilo*/
    for (i = 0; i < (hilos - 1); i++) {
        infos[i] = malloc(sizeof(*infos[i]));
        infos[i]->inicio = (i * actual);
        infos[i]->fin = ((i + 1) * actual - 1);
    }

    infos[hilos - 1] = malloc(sizeof(*infos[hilos]));
    infos[hilos - 1] -> inicio = (i * actual);
    infos[hilos - 1] -> fin = n;
    /*Asigna el proceso de búsqueda lienal a cada hilo*/
    for (i = 0; i < hilos; i++){
        status = pthread_create(&threads[i], NULL, thread_process, infos[i]);
        if (status){
            printf("\nError en thread %i\n", status);
            exit(-1);
        }
    }
    /*Espera a que cada hilo termine exitosamente su tarea*/
    for (i = 0; i < hilos; i++){
        pthread_join(threads[i], (void **)&exit_code);
    }
    return 0;
}

/* FUNCIÓN QUE CALCULA EL NUMERO DE HILOS A CREAR/
/* Recibe: tamaño del arreglo */
/* Devuelve: Entero número de hilos */
/* Descripción: Calcula en número de hilos de acuerdo a la variable
    global MAXTHREADS, realizando una operación modulo entre este y el tamaño del arreglo */
int calc_hilos(int n){
    if (n < THREADS)
        return 1;
    int module = (n % THREADS);
    if (module == 0)
        return THREADS;
    return module;
}