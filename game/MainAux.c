/*
 * MainAux.c
 *
 *  Created on: 21 May 2018
 *      Author: hp envy
 */

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "MainAux.h"
/* 0<=z<n */

int calcIndex(int x, int y, int z,int d1, int d2){
	return ((x)*d1*d2 + (y)*d2 + (z));
}


void printIntArr(int* arr, int arrSize){
	int i;
	printf("[");
	for(i = 0; i <arrSize; i++)
		printf("%d ,", arr[i]);
	printf("]\n");
}

void printDblArr(double* arr, int arrSize){
	int i;
	printf("[");
	for(i = 0; i < arrSize; i++)
		printf("%f ,", arr[i]);
	printf("]\n");
}
