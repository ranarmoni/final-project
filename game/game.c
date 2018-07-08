/*#include "parser.h"
*/
#include "game.h"
#include <stdio.h>
#include "solver.h"
#include "parser.h"


GameBoard board;
GameBoard solution;
int fixedAmnt;
int fullCells;

/*
 * checks whether cell (x,y) is fixed.
 */
int isFixed(int x,int y);
/*
 * creates a deep copy of the game board.
 */
void deepCopy(GameBoard *to, GameBoard *from);
void initBoard(GameBoard *board);



int startGame(){
	int x;
	initBoard(&board);
	initBoard(&solution);
	x = readFixedAmnt();
	/* if EOF was recieved */
	if (x==-1)
		return 0;
	fullCells = x;
	solution = *generateSolution(&solution);
	board = *generateBoard(&solution, &board , x);
	printBoard(board);
	return 1;
}


int setCell(int z, int x, int y){
	if(isFixed(x,y)){
		printf("Error: cell is fixed\n");
		return 0;
	}
	if(!isLegalSet(&board,z+1,x,y)){ /*using z+1 because parser applied minus 1 to values */
		printf("Error: value is invalid\n");
		return 0;
	}
	board.boardMatrix[x][y][0]=z+1;
	fullCells++;
	printBoard(board);
	if(isGameOver())
		printf("Puzzle solved successfully\n");
	return 1;
}


int isLegalSet(GameBoard *board ,int z, int x, int y){
	int i,j,currRow,currCol;


	for(currRow=0;currRow<TABLE_SIZE;++currRow) /*scan relevant column for collisions*/
		if(z==board->boardMatrix[currRow][y][0])
			return 0;

	for(currCol=0;currCol<TABLE_SIZE;++currCol)/*scan relevant row for collisions*/
			if(z==board->boardMatrix[x][currCol][0])
				return 0;


	currRow=x-(x%BLOCK_SIZE);
	currCol=y-(y%BLOCK_SIZE);

	for(i=0;i<BLOCK_SIZE;i++)/*scan relevant block for collisions, starting top left corner.*/
		for(j=0;j<BLOCK_SIZE;j++)
			if(z==board->boardMatrix[currRow+i][currCol+j][0])
				return 0;

	return 1;

}


int isFixed(int x, int y){
	return board.boardMatrix[x][y][1];
}


void hintCell(int x,int y){
	int hint = solution.boardMatrix[x][y][0];
	printf("Hint: set cell to %d \n",hint);
}


void validateBoard(){
	GameBoard newSol, *temp;
	/* ******************************** */
	deepCopy(&newSol, &board);
	temp = hasSolution(&newSol);
	if (temp != NULL){
		solution = *temp;
		printf("Validation passed: board is solvable\n");
	}
	else
		printf("Validation failed: board is unsolvable\n");
}

/*
 * a.	Restart the game by calling startGame().
 */
void restartGame(){
	startGame();
}

/*
 * free space
 * close everything
 */
void exitCommand(){
	printf("Exiting...\n");
	}

/*
 * PRIVATE METHOMDS FOLLOW
 */

/*
 * print the game board
 */
void printBoard(GameBoard board){
	int i, j, k, l, x=0, y=0;

	for(k=0; k<BLOCK_SIZE; k++){
		printf("----------------------------------\n");
		for(l=0; l<BLOCK_SIZE; l++){
		for(i=0; i<BLOCK_SIZE; i++){
				printf("|");
				for(j=0; j<BLOCK_SIZE; j++){
					printf(" ");
					if(board.boardMatrix[x][y][1]==1)
						printf(".");
					else
						printf(" ");
					if(board.boardMatrix[x][y][0]==0)
						printf(" ");
					else
						printf("%d",board.boardMatrix[x][y][0]);
					y++;
				}
				printf(" ");
			}
		printf("|\n");
		y=0;
		x++;
		}
	}
	printf("----------------------------------\n");
}


int isGameOver(){
	return (fullCells == 81);
}
/* copy the content of two gameboards */
void deepCopy(GameBoard *to, GameBoard *from){
	int i,j;

	for (i=0; i<TABLE_SIZE; ++i)
		for (j=0; j<TABLE_SIZE; ++j)
			to->boardMatrix[i][j][0] = from->boardMatrix[i][j][0];
}

void initBoard(GameBoard *board){
	int i,j;

	for(i=0; i<TABLE_SIZE; ++i)
		for(j=0; j<TABLE_SIZE; ++j){
			board->boardMatrix[i][j][0]=0;
			board->boardMatrix[i][j][1]=0;
		}
}
