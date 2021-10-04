/*****************************************************************
(C)Septiembre 2021

EQUIPO: Ponys Salvajes
INTEGRANTES DEL EQUIPO: 
    López Gracia Angel Emmanuel 
    López Hernández Lissete 
    Martínez Martínez Fernando 
    Martínez Ortiz Fabiola Yahel	
  VERSIÓN: 1.0
DESCRIPCIÓN: Programa que calcula el promedio a partir de n datos leidos de una consola o de un archivo indicado en consola.

CURSO: Análisis de algoritmos
    COMPILACIÓN: "gcc [nombre_del_programa].c  -o promedio” 
    EJECUCIÓN: "./promedio n" (Linux y MAC OS)
*****************************************************************/

//LIBRERIAS INCLUIDAS
#include <stdio.h>
#include <stdlib.h>

//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)

/*promedio calcula el promedio de n numeros (numInstrucciones) a partir de los valores de un arreglo (instrucciones).
Recibe: un arreglo de doubles que almacenan los valores a promediar, un entero con el tamaño del arreglo.
Regresa un valor tipo float con el promedio de los valores*/
float promedio(double instrucciones[], int numInstrucciones);
/****************************************/

//PROGRAMA PRINCIPAL
int main(int argc, char const *argv[])
{
    int n;
    double *instrucciones;
    int i;
    if (argc != 2)
    {
        printf("Ingrese n");
        exit(EXIT_FAILURE);
    }
    n = atoi(argv[1]);

    if ((instrucciones = malloc(sizeof(int) * n)) == NULL)
        perror("No se pudo solicitar memoria para el arreglo");
    /*lee numero por numero de un archivo*/
    for (i = 0; i < n; i++)
        scanf("%lf", &instrucciones[i]);
    //Impresion del promedio
    printf("\n%.10e", promedio(instrucciones, n));
}
//DEFINICIÓN DE FUNCIONES
//*****************************************************

/*promedio calcula el promedio de n numeros (numInstrucciones) a partir de ls valores de un arreglo (instrucciones).
Recibe: un arreglo de enteros que almacenan los valores a promediar, un entero con el tamaño del arreglo.
Regresa un valor tipo float con el promedio de los valores*/
float promedio(double instrucciones[], int numInstrucciones)
{
    double suma = 0;
    //hasta que se termine de recorrer el arreglo
    for (int i = 0; i < numInstrucciones; i++)
    {
        //suma todos los valores del arreglo
        suma += instrucciones[i];
    }
    //calcula el promedio
    return (double)suma / (double)numInstrucciones;
}
