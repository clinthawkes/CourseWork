#! /bin/bash

#Number of threads
#for t in 1 2 3 4 5 6 
#do 
    for r in 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2097152 4194304 8388608 
    do    
        #echo NUMT = $t 
        echo ARR_SIZE= $r 
        g++ -DARR_SIZE=$r project4.cpp -o proj -lm -fopenmp
        ./proj
        echo 
    done     
#done 
