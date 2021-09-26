/*****************************************************************
(C)Septiembre 2021

EQUIPO: Ponys Salvajes
INTEGRANTES DEL EQUIPO: 
    López Gracia Angel Emmanuel 
    López Hernández Lissete 
    Martínez Martínez Fernando 
    Martínez Ortiz Fabiola Yahel	
  VERSIÓN: 1.0
DESCRIPCIÓN: Implementación del algoritmo de búsqueda de fibonacci. Mide el tiempo de ejecución del algoritmo. 
			Se toman los valores de entrada de un archivo .txt con números ordenados.

CURSO: Análisis de algoritmos
    COMPILACIÓN: "gcc [nombre_del_programa].c tiempo.c  -o main” 
    EJECUCIÓN: "./main n x" (Linux y MAC OS)
*****************************************************************/

//LIBRERIAS INCLUIDAS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "tiempo.h"
//*****************************************************************

//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)

/* Prototipo para la funcion que implementa el algortimo de busqueda de fibonacci
fib_Search: busca la posicion de un numero x en un arreglo ordenado arr[] mediante la busqueda de fibonacci
Recibe: arr[] arreglo ordenado de enteror
        x     numero buscado enteros
        n     tamaño del arreglo de enteros
Devuelve: posicion del entero x, en caso de no encontrarse retorna un -1
*/
int fib_Search(int arr[], int x, int n);

/*Min: retorna el menor numero entre dos
Recibe: dos numeros enteros
Devuelve: el entero menor*/
int min(int x, int y);

//*******************************************************

//PROGRAMA PRINCIPAL
int main(int argc, char *argv[])
{
    //Variables del main
    int n; //Tamaño del arreglo
    int x; //Numero a buscar
    int *arreglo; //Arreglo que almacena los numeros ordenados en los que se buscara x
    int i, j;     //indices de ciclos

    /* RECEPCIÓN Y DECODIFICACIÓN DE ARGUMENTOS */
    //Condicional *if* se ejecuta en caso de no introducirse exactamente 3 argumentos (Cadena de ejecución,  cadena=n y cadena=x)
    if (argc != 3)
    {
        printf("\nIndicar el tamanio del algoritmo y el numero a buscar. Ejemplo: [user@equipo]$ %s 100 < numeros10millones.txt\n", argv[0]);
        exit(1);
    }
    else
        n = atoi(argv[1]); //Conversion de la cadena de la consola a numero
    x = atoi(argv[2]);     //Conversion de la cadena de la consola a numero

    //Asignacion de memoria dinamica para el arreglo de numeros ordenados
    if ((arreglo = malloc(sizeof(int) * n)) == NULL)
        perror("No se concreto la asignacion de memoria para 'arreglo'");

    //Llenado del arreglo
    for (i = 0; i < n; i++)
        scanf("%d", &arreglo[i]);
//*****************************************************************
	
	//INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO	
	uswtime(&utime0, &stime0, &wtime0);

	//ALGORITMO	
	//Llamada a la función del algoritmo
    printf("Encontrado en la posición: %d\t", fib_Search(arreglo, x, n));
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

	//FORMATO PARA OBTENER TIEMPO DE EJECUCIÓN 
	printf("Insrt %15.10e  %21.10e %21.10e %21.10f%% \n", wtime1 - wtime0,utime1 - utime0,stime1 - stime0,100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));

	//Finaliza programa 
	exit (0);	
}

//DEFINICIÓN DE FUNCIONES 
//************************************************************************.
/*FUNCIÓN QUE IMPLEMENTA EL ALGORITMO DE BÚSQUEDA DE FIBONACCI*/
/*
Recibe: arr[] arreglo ordenado de enteror
        x     numero buscado enteros
        n     tamaño del arreglo de enteros
Devuelve: posicion del entero x, en caso de no encontrarse retorna un -1
Descripción: busca la posicion de un numero x en un arreglo ordenado arr[] mediante la busqueda de fibonacci
*/
int fib_Search(int arr[], int x, int n)
{
    /* Variables:
nFibMay: almacena un numero de la serie de fibonacci
nFibMed: almacena el numero anterior a nFibMay en la serie de fibonacci
nFibMin: almacena el numero anterior a nFibMed en la serie de fibonacci
*/
    int nFibMin, nFibMed, nFibMay;
    //Inicializacion de las variables que almacenan los numeros de fibonacci
    nFibMin = 0;
    nFibMed = 1;
    nFibMay = nFibMin + nFibMed;
    /*Se busca el numero de la serie de fibonacci que sea mayor o igual al tamaño del arreglo ordenado de enteros*/
    while (nFibMay < n)
    {
        nFibMin = nFibMed;
        nFibMed = nFibMay;
        nFibMay = nFibMin + nFibMed;
    }
    /*Variable que excluye porciones del arreglo ya analizadas*/
    int desplazamiento = -1;

    while (nFibMay > 1)
    {
        /*Asignacion de posiciones de prueba en donde se buscara el numero x*/
        int i = min(desplazamiento + nFibMin, n - 1);
        /*Si el dato de la posicion de prueba es menor o mayor al valor buscado se buscara en porciones del arreglo mas pequeñas cada vez, excluyendo porciones del arreglo ya analizadas*/
        if (arr[i] < x)
        {
            nFibMay = nFibMed;
            nFibMed = nFibMin;
            nFibMin = nFibMay - nFibMed;
            desplazamiento = i;
        }
        else if (arr[i] > x)
        {
            nFibMay = nFibMin;
            nFibMed = nFibMed - nFibMin;
            nFibMin = nFibMay - nFibMed;
        }
        else
            return i; //En caso de encontrarse el valor buscado se retorna su ubicacion en el arreglo
    }
    /*Si en ningun caso de los anteriores se encontro el dato buscado se busca en la ultima posicion del arreglo, em caso de ser encontrado se retorna la posicion.*/
    if (nFibMed && arr[desplazamiento + 1] == x)
    {
        return desplazamiento + 1;
    }
    return -1; //Si el dato x no se encuentra se retorna un -1
}
/*FUNCIÓN QUE DETERMINA EL MENOR DE DOS NUMEROS*/
/*Min: retorna el menor numero entre dos
Recibe: dos numeros enteros
Devuelve: el entero menor*/
int min(int x, int y)
{
    return (x <= y) ? x : y;
}
