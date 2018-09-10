#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int loadFile(char *filename, GameBoard newBoard){
	int n,m,val,i=0,*boardMatrix;
	char c;

	FILE *fptr;
	fptr = fopen(filename,"r");
	if(!fptr)
		return 0;

	if(!fscanf(fptr,"%d",&n) || !fscanf(fptr,"%d",&m))
		return 0;

	boardMatrix = (int*)calloc(n*m*3,sizeof(int));

	while(fscanf(fptr,"%d",&val)){
		boardMatrix[i] = val;
		c = fgetc(fptr);
		boardMatrix[i+1] = (c=='.');
		i += 3;
	}

	newBoard.board = boardMatrix;
	return 1;
}
