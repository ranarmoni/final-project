#include "solver.h"
#include <stdlib.h>
#include <stdio.h>

int backtracking(GameBoard *board, int random, int x, int y);


void setSeed(int seed){
	srand(seed);
}



GameBoard* generateSolution(GameBoard *board){
	backtracking(board, 1, 0, 0);
	return board;
}

GameBoard* generateBoard(GameBoard *solution,GameBoard *board, int fixedAmnt){
	int i,x, y;

	for(i=0; i<fixedAmnt; ++i){
		x = (rand() % 9);
		y = (rand() % 9);

		if( board->boardMatrix[x][y][0] == 0 ){
			board->boardMatrix[x][y][0] = solution->boardMatrix[x][y][0];
			board->boardMatrix[x][y][1] = 1;
		}
		else
			--i;
	}
	return board;
}

GameBoard* hasSolution(GameBoard *board){
	printf("copy of the curr board\n");
	printBoard(*board);
	if( backtracking(board, 0, 0, 0) == 1)
		return board;
	else
		return NULL;
}

int backtracking(GameBoard *board, int isRandom, int x, int y){

	int i, currVal = 0;
	int possibleVals[TABLE_SIZE],
		options = 0,
		success=0,
		nextX = x,
		nextY = y;
	/*set the next cell coordinates */
	++nextX;
	if(nextX==TABLE_SIZE){
		nextX=0;
		++nextY;
	}


	/*
	 * stop if the end of the table was reached
	 */
	if(x==TABLE_SIZE || y==TABLE_SIZE){
		printf("finished solving\n");
		return 1;
	}
	/*
	 * check if cell is blank
	 */
	if(board->boardMatrix[x][y][0] == 0){
		/*
		 * find all possible values for the cell based on current state
		 */
		for(i=0; i<TABLE_SIZE; ++i){
			possibleVals[i] = isLegalSet(board,i+1,x,y);
			options += possibleVals[i];
		}

		while(options>0 && success==0){

			/*
			 * choose a vlaue for the cell
			 */
			if(isRandom)
				currVal = rand()%TABLE_SIZE;
			while(possibleVals[currVal] == 0){
				if(isRandom)
					currVal = rand()%TABLE_SIZE;
				else
					currVal++;
			}

			/*take the used value out	 */
			possibleVals[currVal] = 0;
			--options;

			/*
			 * place the value in the cell and make the recursive call
			 */
			board->boardMatrix[x][y][0] = currVal+1;

			success = backtracking(board,isRandom,nextX,nextY);
		}
		if (success == 0)
			board->boardMatrix[x][y][0] = 0;
		return success;
	}

	return backtracking(board,isRandom,nextX,nextY);
}
