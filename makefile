CC = gcc
CFLAGS = -W -Wall -Werror -pedantic
OBJ = conversion.o main.o spiralmatrix.o user.o

spiral-matrix.out: $(OBJ)
	$(CC) $(CFLAGS) -o spiral-matrix.out $(OBJ) -lm

conversion.o: conversion.c conversion.h
	$(CC) $(CFLAGS) -c conversion.c -o conversion.o

spiralmatrix.o: spiralmatrix.c spiralmatrix.h
	$(CC) $(CFLAGS) -c spiralmatrix.c -o spiralmatrix.o

user.o: user.c user.h
	$(CC) $(CFLAGS) -c user.c -o user.o

main.o: main.c conversion.h spiralmatrix.h user.h
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f $(OBJ) spiral-matrix.out