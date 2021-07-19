#! /bin/bash

#Number of threads
for t in 1 2 3 4 5 6 
do 
    for r in 4 10 25 50 100 250 500 1000 2000 5000 10000  
    do    
        echo NUMT = $t 
        echo NUMNODES = $r 
        g++ -DNUMT=$t  -DNUMNODES=$r project2.c -o prog -lm -fopenmp
        ./prog
        echo 
    done     
done 
