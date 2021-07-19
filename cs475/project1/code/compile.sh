#! /bin/bash

#Number of threads
for t in 1 2 3 4 5 6 
do 
    for r in 10 100 1000 10000 100000 1000000 
    do    
        echo NUMT = $t 
        echo NUMTRIALS = $r 
        g++ -DNUMT=$t  -DNUMTRIALS=$r project1.c -o prog -lm -fopenmp
        ./prog
        echo 
    done     
done 
