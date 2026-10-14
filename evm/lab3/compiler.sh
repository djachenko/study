#!/bin/sh

cc -xO0 -S -o 3.0.s 3.c
cc -xO0 -xarch=amd64a -S -o 3.0_arch.s 3.c
cc -xO3 -S -o 3.3.s 3.c
cc -xO3 -xarch=amd64a -S -o 3.3_arch.s 3.c

