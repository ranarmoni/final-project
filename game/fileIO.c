
#include "MainAux.h"
#include <stdio.h>
#include <stdlib.h>

int BLOCK_SIZE_N;
int BLOCK_SIZE_M;
int TABLE_SIZE;

int loadFile(char *filename, GameBoard *newBoard){
	int n=0,m=0,val,i=0,*boardMatrix;
	char c;

	FILE *fptr;
	fptr = fopen(filename,"r");
	if(!fptr)
		return 0;

	printf("loaded file\n");

	if(!fscanf(fptr,"%d",&n) || !fscanf(fptr,"%d",&m))
		return 0;

	printf("loaded dim %d,%d\n", m, n);
	BLOCK_SIZE_M = m;
	BLOCK_SIZE_N = n;
	TABLE_SIZE = m*n;
	boardMatrix = (int*)calloc(TABLE_SIZE*TABLE_SIZE*3,sizeof(int));

	while(fscanf(fptr,"%d",&val) != -1){

		printf("loaded value %d\n", val);
		boardMatrix[i] = val;
		c = fgetc(fptr);
		boardMatrix[i+1] = (c=='.');
		i += 3;
	}
	printf("out of loop\n");
	fclose(fptr);
	printf("closed file\n");
	newBoard->board = boardMatrix;
	printf("matrix loaded\n");
	return 1;
}

int saveFile(char *filename, GameBoard *newBoard){
	int i,j,
		*boardMatrix = newBoard->board;
	FILE *sFile = fopen(filename,"w+");

	if(!sFile)
		return 0;


	printf("dims are %d %d",BLOCK_SIZE_N,BLOCK_SIZE_M);

	fprintf(sFile,"%d ",BLOCK_SIZE_N);
	printf("wrote m and n\n");
	fprintf(sFile,"%d\n",BLOCK_SIZE_M);

	printf("%d\n",TABLE_SIZE);
	for(i=0; i<TABLE_SIZE;i++){
		for(j=0; j<TABLE_SIZE;j++){
			fprintf(sFile,"%d",boardMatrix[calcIndex(i,j,0,TABLE_SIZE,3)]);
			if(boardMatrix[calcIndex(i,j,1,TABLE_SIZE,3)] == 1)
				fprintf(sFile,"%c",'.');
			if(j != TABLE_SIZE-1)
				fprintf(sFile,"%c",' ');
			else if(i != TABLE_SIZE-1)
				fprintf(sFile,"%c",'\n');
		}
	}

	fclose(sFile);
	return 1;
}

int main() {
	GameBoard boardel;
	loadFile("in",&boardel);
	printIntArr(boardel.board,48);
	saveFile("out", &boardel);
	return 1;
}

