
#include "MainAux.h"
#include <stdio.h>
#include <stdlib.h>

int BLOCK_SIZE_N;
int BLOCK_SIZE_M;
int TABLE_SIZE;
int fullCells;

int loadFile(char *filename, GameBoard *newBoard){
	int n=0,m=0,val,i=0,*boardMatrix,fullCellsCount = 0;
	char c;

	FILE *fptr;
	fptr = fopen(filename,"r");
	if(!fptr)
		return 0;

	if(!fscanf(fptr,"%d",&m) || !fscanf(fptr,"%d",&n))
		return 0;

	BLOCK_SIZE_M = m;
	BLOCK_SIZE_N = n;
	TABLE_SIZE = m*n;
	boardMatrix = (int*)calloc(TABLE_SIZE*TABLE_SIZE*3,sizeof(int));

	if(!boardMatrix){
		printf("Error: calloc has failed\n");
		exit(0);
	}

	while(fscanf(fptr,"%d",&val) != -1){
		if(val!=0)
			fullCellsCount++;
		boardMatrix[i] = val;
		c = fgetc(fptr);
		boardMatrix[i+1] = (c=='.');
		i += 3;
	}

	if(fclose(fptr) != 0){
		printf("Problem while closing the file");
		exit(0);
	}
	newBoard->board = boardMatrix;
	fullCells = fullCellsCount;
	return 1;
}

int saveFile(char *filename, GameBoard *newBoard){
	int i,j,
		*boardMatrix = newBoard->board;
	FILE *sFile = fopen(filename,"w+");

	if(!sFile)
		return 0;

	fprintf(sFile,"%d %d\n",BLOCK_SIZE_M, BLOCK_SIZE_N);

	for(i=0; i<TABLE_SIZE;i++){
		for(j=0; j<TABLE_SIZE;j++){
			fprintf(sFile,"%d",boardMatrix[calcIndex(i,j,0,TABLE_SIZE,3)]);
			if(boardMatrix[calcIndex(i,j,1,TABLE_SIZE,3)] == 1)
				fprintf(sFile,".");
			if(j != TABLE_SIZE-1)
				fprintf(sFile," ");
			else
				fprintf(sFile,"\n");
		}
	}

	if(fclose(sFile) != 0){
		printf("Problem while closing the file");
		exit(0);
	}

	return 1;
}

