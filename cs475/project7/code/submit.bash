#!/bin/bash

# for i in 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2097152 4194304 8388608
# do
#     for j in 32 64 128 256 
#     do
        g++ -w -o project7 project7.cpp /opt/cuda/lib64/libOpenCL.so.1.1 -lm -fopenmp
        ./project7
    # done
# done
