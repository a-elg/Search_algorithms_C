#!/bin/bash

#Script para compilar el algoritmo de busqueda exponencial implementado con hilos en un ambiente LINUX
# Compilacion
gcc exponential_threads.c tiempo.c -lpthread -o exp
gcc Promedio.c  -o promedio

#Tamaño de problema
n=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000);

#Numeros a buscar
x=(322486 14700764 3128036 6337399 61396 10393545 2147445644 1295390003 450057883 187645041 1980098116 152503 5000 1493283650 214826 1843349527 1360839354 2109248666 2147470852 0);

#Ejecuciones 
for a in ${n[*]}
 do
 
 	for b in ${x[*]}
 	do
   #Obtencion de tiempos de ejecucion para todas las x de una n
        ./exp "$a" "$b" < 10millones.txt  >> "./TiemposExp.txt"       
        done
        #Calculo del promedio de los tiempos obtenidos
      ./promedio 20 < TiemposExp.txt >> salPromedioExp.txt
      #Borrado del archivo para el siguiente calculo
       echo " "  > "./TiemposExp.txt"
 done
