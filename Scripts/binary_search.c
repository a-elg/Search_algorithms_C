/*****************************************************************
(C)Septiembre 2021

EQUIPO: Ponys Salvajes
INTEGRANTES DEL EQUIPO: 
    López Gracia Angel Emmanuel 
    López Hernández Lissete 
    Martínez Martínez Fernando 
    Martínez Ortiz Fabiola Yahel	
  VERSIÓN: 1.0
DESCRIPCIÓN: Implementación del algoritmo de búsqueda lineal. Mide el tiempo de ejecución del algoritmo. 
			Se toman los valores de entrada de un archivo .txt con números ordenados.

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
/*prototipo para la función que implementa el algoritmo de búsqueda binaria iterativa*/
//int binary_search(int A[], int n, int x);
int binary_search(int A[], int l, int r, int x);
//*****************************************************************

//PROGRAMA PRINCIPAL
int main(int argc, char *argv[])
{
	int x[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0};
	double sumaTiempos = 0, sumaCPU = 0, sumaES = 0;
	int *A;
	//int x = 0;
	int tam, result;
	//Variables para ciclos
	int i, j;
	//Variables para medición de tiempos
	double utime0, stime0, wtime0, utime1, stime1, wtime1;

	/* RECEPCIÓN Y DECODIFICACIÓN DE ARGUMENTOS */
	//Condicional *if* es verdadera en caso de no introducirse exactamente 3 argumentos (Cadena de ejecución, numero=tamaño y x = )
	if (argc != 2)
	{
		printf("\nIndicar el tamanio del arreglo y numeroa buscar, por favor - Ejemplo: [user@equipo]$ %s 100 24 < numeros10millones.txt\n", argv[0]);
		exit(1);
	}
	else
	{
		tam = atoi(argv[1]); //Tomar el segundo argumento como tamaño del algoritmo
							 // x = atoi(argv[2]); //Tomar el tercer argumento como el número a buscar
	}

	//Asignacion de memoria dinamica para el A de numeros a ordenar
	if ((A = malloc(sizeof(int) * tam)) == NULL)
		perror("La asignacion dinamica no se realizo correctamente");
	//Llenado del arreglo
	for (i = 0; i < tam; i++)
	{
		scanf("%d", &A[i]);
	}
	//*****************************************************************

	//INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO
	for (i = 0; i < 20; i++)
	{
		uswtime(&utime0, &stime0, &wtime0);

		//ALGORITMO
		//Llamada a la función del algoritmo
		result = binary_search(A, 0, tam - 1, x[i]);
		//Valida el resultado para saber si se encontró o no el número
		//(result == -1)
		//  ? printf("El elemento no se encunetra en el arreglo")
		//: printf("El elemento se encunetra en el indice: \t %d", result);

		//EVALUAR LOS TIEMPOS DE EJECUCIÓN
		uswtime(&utime1, &stime1, &wtime1);

		/*
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
	*/
		sumaTiempos += wtime1 - wtime0;
		sumaCPU += utime1 - utime0;
		sumaES += stime1 - stime0;
	}
	//Linea de impresion para script4.sh
	printf("Busqueda binaria\t\t %d\t\t%.10e\t\t%.10e\t\t%.10e\n", tam, sumaTiempos / 20, sumaCPU / 20, sumaES / 20);
	//FORMATO PARA OBTENER TIEMPO DE EJECUCIÓN
	//printf("Insrt %15.10e  %21.10e %21.10e %21.10f%% \n", wtime1 - wtime0,utime1 - utime0,stime1 - stime0,100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));

	//Finaliza programa
	exit(0);
}

//DEFINICIÓN DE FUNCIONES
//************************************************************************

/*FUNCIÓN QUE IMPLEMENTA EL ALGORITMO DE BÚSQUEDA BINARIA*/
/* Recibe: Arreglo de enteros A[], entero tamanio con el tamaño de A[] y entero x con el número a buscar	*/
/* Devuelve: Entero (bandera para saber que no se encunetra o el índice si está) */
/* Descripción: Busca en un arreglo ordenado mediante la división del intervalo de búsqueda
   a la mitad. Comenzando con el tamaño total del arreglo, compara si el 
   valor a buscar es mayor o menor al valor de la mitad del arreglo, con ello decide si buscar 
   en el subarreglo anterior o posterior a este valor. Se repite con los subareglos hasta encontrar el número.  */
int binary_search(int A[], int l, int r, int x)
{
	// Mientras el inicio sea menor o igual al final del arreglo
	while (l <= r)
	{
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
