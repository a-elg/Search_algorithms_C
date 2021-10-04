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
			Se toman los valores de entrada del archivo .txt con los 10 millones de números.

CURSO: Análisis de algoritmos
    COMPILACIÓN: "gcc [nombre_del_programa].c tiempo.x  -o main” 
    EJECUCIÓN: "./main n x < numeros10millones" (Linux y MAC OS)
    EJECUCIÓN: "./main 1000 2041447909 < numeros10millones.txt" (Linux y MAC OS)
	                        2147483647
*****************************************************************/

//LIBRERIAS INCLUIDAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include "tiempo.h"
#include "tiempo.h"
//*****************************************************************
//DECLARACION DE ESTRUCTURAS
struct nodo_arbol
{ //Cada nodo tiene 2 hijo, un valor y un padre
	int valor;
	struct nodo_arbol *h_derecho;
	struct nodo_arbol *h_izquierdo;
	struct nodo_arbol *padre;
};
typedef struct nodo_arbol nodo;
//*****************************************************************
//VARIABLES GLOBALES
nodo *raiz; //raiz del árbol
//DECLARACIÓN DE FUNCIONES (PROTOTIPOS)
/*prototipo para la función que crea un nodo (hoja) para ser insertado*/
nodo *crearNodo(int dato);
/*prototipo para la función que inserta un valor en el ABB*/
void insertar(int dato);
/*prototipo para la función que busca el valor en el ABB generado*/
int buscar(int dato);
//*****************************************************************

//PROGRAMA PRINCIPAL
int main(int argc, char *argv[])
{
	int x[] = {322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1360839354, 2109248666, 2147470852, 0};
	double sumaTiempos = 0, sumaCPU = 0, sumaES = 0;
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
		printf("\nIndicar el tamanio del algoritmo y el valor a buscar, por favor - Ejemplo: [user@equipo]$ %s 100 30495 < numeros10millones.txt\n", argv[0]);
		exit(1);
	}
	else
	{
		tam = atoi(argv[1]); //Tomar el segundo argumento como tamaño del algoritmo
							 //x = atoi(argv[2]);	 //Tomar el tercer argumento como el número a buscar
	}

	int aux; //Auxiliar para escanear números
	scanf("%d", &aux);
	raiz = crearNodo(aux);
	//Llenado del árbol
	for (i = 1; i < tam; i++)
	{
		scanf("%d", &aux);
		insertar(aux);
	}
	//*****************************************************************

	//INICIAR EL CONTEO DEL TIEMPO PARA LAS EVALUACIONES DE RENDIMIENTO
	for (i = 0; i < 20; i++)
	{
		uswtime(&utime0, &stime0, &wtime0);

		//ALGORITMO
		//Llamada a la función del algoritmo
		result = buscar(x[i]);
		//Valida el resultado para saber si se encontró o no el número
		//(result != -1)
		//	? printf("Elemento encontrado\n")
		//	: printf("Elemento no encontrado\n");

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
		sumaTiempos += wtime1 - wtime0;
		sumaCPU += utime1 - utime0;
		sumaES += stime1 - stime0;
	}
	//Linea de impresion para script4.sh
	printf("Busqueda en ABB\t\t %d\t\t%.10e\t\t%.10e\t\t%.10e\n", tam, sumaTiempos / 20, sumaCPU / 20, sumaES / 20);
	//FORMATO PARA OBTENER TIEMPO DE EJECUCIÓN
	//printf("ABB %15.10e  %21.10e %21.10e %21.10f%% \n", wtime1 - wtime0,utime1 - utime0,stime1 - stime0,100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));

	//Finaliza programa
	exit(0);
}

//DEFINICIÓN DE FUNCIONES
//************************************************************************
/*FUNCIÓN QUE CREA UN NODO (hoja) PARA SER INSERTADO*/
/* Recibe: entero dato*/
/* Devuelve: apuntador de tipo nodo */
nodo *crearNodo(int dato)
{
	//Apartar espacio para un nuevo nodo
	nodo *nuevo_nodo = (nodo *)malloc(sizeof(nodo));

	//Inicializamos los valores del nodo
	nuevo_nodo->valor = dato;
	nuevo_nodo->h_derecho = NULL;
	nuevo_nodo->h_izquierdo = NULL;
	nuevo_nodo->padre = NULL;

	//Regresar la dirección apartada
	return nuevo_nodo;
}

/*FUNCIÓN QUE INSERTA UN VALOR EN EL ÁRBOL*/
/* Recibe: entero dato*/
/* Devuelve: vacío */
void insertar(int dato)
{
	nodo *aux = raiz;
	nodo *nuevo_nodo = crearNodo(dato);
	while (1)
	{
		if (dato > aux->valor)
		{ //¿El dato es estrictamente mayor que el del nodo en revisón?
			if (aux->h_derecho)
			{						  //¿Tiene hijo derecho?
				aux = aux->h_derecho; //Repetir el ciclo, pero iniciando desde el hijo derecho
				continue;
			}
			else
			{ //No tiene hijo derecho
				//Al nuevo nodo, conectarlo con una hoja, tanto de padre a hijo, como de hijo a padre
				aux->h_derecho = nuevo_nodo;
				nuevo_nodo->padre = aux;
				break;
			}
		}
		else
		{ //El dato es menor o igual al dato del nodo en revisión
			if (aux->h_izquierdo)
			{							//¿Tiene hijo izquierdo?
				aux = aux->h_izquierdo; //Repetir el ciclo, pero iniciando desde el hijo izquierdo
				continue;
			}
			else
			{ //No tiene hijo izquierdo
				//Al nuevo nodo, conectarlo con una hoja, tanto de padre a hijo, como de hijo a padre
				aux->h_izquierdo = nuevo_nodo;
				nuevo_nodo->padre = aux;
				break;
			}
		}
	}
}

//FUNCIÓN QUE IMPLEMENTA EL ALGORITMO DE BÚSQUEDA en un árbol binario de búsqueda, recibe el dato a buscar
//Devuelve el número buscado si se encontró y un 0 si no se encontró.
int buscar(int x)
{
	int aux; //Variable para evitar calcular muchas veces nodo->valor
	nodo *nodo_en_revision = raiz;
	while (nodo_en_revision)
	{ //Cuando se vuelva null, el ciclo se cerrará
		aux = nodo_en_revision->valor;
		if (aux == x)
			return x;
		else
		{
			if (x > aux) //ir a rama derecha
				nodo_en_revision = nodo_en_revision->h_derecho;
			else
			{ //x<= ir a rama izquierda
				nodo_en_revision = nodo_en_revision->h_izquierdo;
			}
		}
	}
	return -1;
}