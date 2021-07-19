#! /bin/bash

#Number of threads
for t in 1 4 
do 
    echo NUMT = $t
    g++ -DNUMT=$t project0.c -o prog -lm -fopenmp
    ./prog
done 
