/*
 * test.c
 *
 *  Created on: 15 Aug. 2018
 *      Author: hp envy
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
	int * arr = malloc(sizeof(int)*4);
	arr[0] = 1;
	arr[1] = 2;
	printf("%d", (int)sizeof(arr));

	return 1;
}
