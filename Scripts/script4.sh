#!/bin/bash

#Compilacion de programas 
#Script para ejecutar 5 algoritmos de busqueda

#Compilacion
gcc linear_search.c tiempo.c -o linear         #Busqueda lineal   
gcc binary_search.c tiempo.c -o binary         #Busqueda binaria
gcc exponential_search.c tiempo.c  -o exponential            #Busqueda exponencial
gcc ABB.c tiempo.c -o ABB        #Busqueda en ABB
gcc fibonacci_search.c tiempo.c -o fibonacci          #Busqueda de fibonacci

# Nota: Cada algoritmo contiene los numeros a buscar en su implementacion, por ello en el presente script se indica unicamente el tamaño de problema
# Archivos utilizados: 
#      numeros10millones.txt: contiene un arreglo desordenado
#      10millones.txt: contiene un arreglo ordenado

#Tamaño de problema para cada algoritmo
n=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000);
#Ejecuciones 
for a in ${n[*]}
 do
        ./linear "$a" < numeros10millones.txt  >> "./TiemposReales2.txt"
 done
 for a in ${n[*]}
 do
        ./binary "$a" < 10millones.txt  >> "./TiemposReales2.txt"
 done
 for a in ${n[*]}
 do
        ./exponential "$a" < 10millones.txt  >> "./TiemposReales2.txt"
 done
 for a in ${n[*]}
 do
        ./ABB "$a" < numeros10millones.txt  >> "./TiemposReales2.txt"
 done
 for a in ${n[*]}
 do
        ./fibonacci "$a" < 10millones.txt  >> "./TiemposReales2.txt"
 done
