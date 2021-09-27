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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

//ESTRUCTURAS Y VARIABLES GLOBALES

/*Datos contiene un arreglo y el tamaño de dicho arreglo.
La estructura se pasa a los hilos*/
typedef struct
{
    int *arreglo;
    int n;
    int* pos;
} datos;
int x;
int contador;

//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)

/*Min: retorna el menor numero entre dos
Recibe: dos numeros enteros
Devuelve: el entero menor*/
int min(int x, int y);

/*fib_Search: busca la posicion de un numero x en un arreglo ordenado arr[] mediante la busqueda de fibonacci
Recibe: arr[] arreglo ordenado de enteror
        x     numero buscado enteros
        n     tamaño del arreglo de enteros
Devuelve: posicion del entero x, en caso de no encontrarse retorna un -1
*/
void* fib_Search(void *dato);
//*******************************************************

//PROGRAMA PRINCIPAL

int main(int argc, char *argv[])
{
    int n; //Tamaño del arreglo
    int pos;
    //Variables del main
    //Hilos
    pthread_t Hilos[2];      //Declaracion del arreglo con dos hilos
    datos arreglOrdenado[2]; //Arreglo que contiene la estructura datos (n y arreglo de cada hilo)

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
    pos=-1;
    for (i = 0; i < 2; i++)
    {
        arreglOrdenado[i].arreglo = &arreglo[(n / 2) * i]; //Asignacion de direcciones iniciales de cada arreglo
        arreglOrdenado[i].n = (n / 2) * (i + 1);           //Asignacion de tamaños de cada arreglo
        arreglOrdenado[i].pos=&pos;
        pthread_create(&Hilos[i], NULL, fib_Search, (void *)&arreglOrdenado[i]);//Creacion de 2 hilos que ejecutan la funcion fib_search y reciben como parametro el arreglo ordenado
    }

    for (i = 0; i < 2; i++)
        pthread_join(Hilos[i], NULL);

    printf("Encontrado en la posicion: %d\t", pos);

    /*  printf("\nn=%d\tx=%d\tM2=%d\tM1=%d\tM=%d\n",n,x, nFibMin, nFibMed,nFibMay);
  float fibo = 2.078087 * log(n) + 1.672276;
  float formula=round(fibo)-2; */

    return 0;
}

/*Min: retorna el menor numero entre dos
Recibe: dos numeros enteros
Devuelve: el entero menor*/
int min(int x, int y)
{
    return (x <= y) ? x : y;
}
/*fib_Search: busca la posicion de un numero x en un arreglo ordenado arr[] mediante la busqueda de fibonacci
Recibe: arr[] arreglo ordenado de enteror
        x     numero buscado enteros
        n     tamaño del arreglo de enteros
Devuelve: posicion del entero x, en caso de no encontrarse retorna un -1
*/
void* fib_Search(void *dato)
{
    datos *arreglOrdenado = (datos *)dato;
    if (*(arreglOrdenado->pos) != -1)
    {
        pthread_exit(NULL); //Termina la llamada de un hilo
    }
    else
    {
        
        int n = (int)arreglOrdenado->n;
        int* arr = (int *)arreglOrdenado->arreglo;
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
                contador++;
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
            {
                *(arreglOrdenado->pos) = i; //En caso de encontrarse el valor buscado se retorna su ubicacion en el arreglo
                pthread_exit(NULL);
            }
        }
        /*Si en ningun caso de los anteriores se encontro el dato buscado se busca en la ultima posicion del arreglo, en caso de ser encontrado se retorna la posicion.*/
        if (nFibMed && arr[desplazamiento + 1] == x)
        {
            *(arreglOrdenado->pos) = desplazamiento + 1;
            pthread_exit(NULL);
        }
        *(arreglOrdenado->pos) = -1; //Si el dato x no se encuentra se retorna un -1
        
    }
    pthread_exit(NULL);
}
