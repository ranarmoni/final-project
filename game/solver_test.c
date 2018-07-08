/*
 * solver_test.c
 *
 *  Created on: 20 May 2018
 *      Author: hp envy
 */

#include "solver.h"
#include <stdio.h>

int main(void){

	GameBoard board;
/*
	int i=0;
	int j=0;
	int n=0;
	for(;i<9;i++){
		for(;j<9;j++){
			board.boardMatrix[i][j][0]=n;
			n++;
		}
	}


	printf("check if valid 2,2,2: %d\n",isLegalSet(board, 2, 2, 2));
	printf("check if valid 2,2,4: %d\n",isLegalSet(board, 2, 2, 4));
	printf("check if valid 2,2,1: %d\n",isLegalSet(board, 2, 2, 1));
	printf("check if valid 2,2,8: %d\n",isLegalSet(board, 2, 2, 8));
*/

	board = *generateSolution(&board);
	printBoard(board);


	}

