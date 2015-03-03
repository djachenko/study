#!/bin/bash

#PBS -V
#PBS -q fitq
#PBS -l select=2:ncpus=8
#PBS -l walltime=00:30:00

########### Task name #########

#PBS -N output

########### Put output to $HOME #########

##PBS -k oe

#########################################

#PBS -j oe

date

cd $PBS_O_WORKDIR

pwd

mpirun -np 16 ./a.out

date
