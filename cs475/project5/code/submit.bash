#!/bin/bash
#SBATCH -J MatrixMult
#SBATCH -A cs475-575
#SBATCH -p class
#SBATCH --gres=gpu:1
#SBATCH -o matrixmul.out
#SBATCH -e matrixmul.err
#SBATCH --mail-type=BEGIN,END,FAIL
#SBATCH --mail-user=hawkesc@oregonstate.edu
/usr/local/apps/cuda/cuda-10.1/bin/nvcc -o matrixMul project5.cu
./matrixMul
