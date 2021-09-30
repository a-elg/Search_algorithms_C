#!/bin/bash
#Compilacion de programas 
gcc linear_search.c tiempo.c -o linear
gcc binary_seach.c tiempo.c -o binary
gcc exponential_search.c tiempo.c  -o exponential
gcc ABB.c tiempo.c -o ABB
gcc fibonacci_search.c tiempo.c -o fibonacci

n=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000);
b=(322486 14700764 3128026 6337399 61396 10393545 2147445644 1295390003 450057883 187645041 1980098116 152503 5000 1493283650 214826 1843349527 1360839354 2109248666 2147470852 0);

#Ejecucion
for a in ${n[*]}
do
    echo "VALOR DE N : $a"  >> "./punto4Linear.txt"
    for x in ${b[*]}
    do
        echo "x:$x"  >> "./punto4Linear.txt"
        ./linear "$a" "$x" < numeros10millones.txt  >> "./punto4Linear.txt"
    done
done

for a in ${n[*]}
do
    echo "VALOR DE N : $a"  >> "./punto4Binary.txt"
    for x in ${b[*]}
    do
        echo "x:$x"  >> "./punto4Binary.txt"
        ./binary "$a" "$x" < 10millones.txt  >> "./punto4Binary.txt"
    done
done

for a in ${n[*]}
do
    echo "VALOR DE N : $a"  >> "./punto4Exponential.txt"
    for x in ${b[*]}
    do
        echo "x:$x"  >> "./punto4Exponential.txt"
        ./exponential "$a" "$x" < 10millones.txt  >> "./punto4Exponential.txt"
    done
done

for a in ${n[*]}
do
    echo "VALOR DE N : $a"  >> "./punto4ABB.txt"
    for x in ${b[*]}
    do
        echo "x:$x"  >> "./punto4ABB.txt"
        ./ABB "$a" "$x" < 10millones.txt  >> "./punto4ABB.txt"
    done
done

for a in ${n[*]}
do
    echo "VALOR DE N : $a"  >> "./punto4Fibonacci.txt"
    for x in ${b[*]}
    do
        echo "x:$x"  >> "./punto4Fibonacci.txt"
        ./fibonacci "$a" "$x" < 10millones.txt  >> "./punto4Fibonacci.txt"
    done
done