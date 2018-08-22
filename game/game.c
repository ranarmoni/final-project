/*#include "parser.h"
*/
#include "game.h"
#include <stdio.h>
#include "solver.h"
#include "parser.h"


GameBoard board;
GameBoard solution;
ActionList actionList;
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
	/* do not delete! */
	address = (char*)calloc(256,sizeof(char));
	return 1;
}


int setCell(int z, int x, int y){
	if(isFixed(x,y)){
		printf("Error: cell is fixed\n");
		return 0;
	}

	board.boardMatrix[x][y][0]=z+1;
	markErrors(&board,z+1,x,y);
	fullCells++;
	printBoard(board);
	if(isGameOver())
		printf("Puzzle solved successfully\n");
	return 1;
}

/*
int isLegalSet(GameBoard *board ,int z, int x, int y){
	int i,j,currRow,currCol;


	for(currRow=0;currRow<BLOCK_SIZE_M;++currRow) //scan relevant column for collisions
		if(z==board->boardMatrix[currRow][y][0])
			return 0;

	for(currCol=0;currCol<BLOCK_SIZE_N;++currCol)//scan relevant row for collisions
			if(z==board->boardMatrix[x][currCol][0])
				return 0;


	// check again if rows/cols & x/y match
	currRow=x-(x%BLOCK_SIZE_N);
	currCol=y-(y%BLOCK_SIZE_M);

	for(i=0;i<BLOCK_SIZE_N;i++)//scan relevant block for collisions, starting top left corner.
		for(j=0;j<BLOCK_SIZE_M;j++)
			if(z==board->boardMatrix[currRow+i][currCol+j][0])
				return 0;

	return 1;
}

*/

int boardHasError(GameBoard *board){
	int i,j,N=BLOCK_SIZE_N+BLOCK_SIZE_M;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			if hasError(board,i,j)
				return 1;
	return 0;
}


int hasError(GameBoard *board ,int x, int y){
	int i,j,currRow,currCol;
	z=board->boardMatrix[x][y][0];


	for(currRow=0;currRow<BLOCK_SIZE_M;++currRow) /*scan relevant column for collisions*/
		if(z==board->boardMatrix[currRow][y][0])
			return 1;

	for(currCol=0;currCol<BLOCK_SIZE_N;++currCol)/*scan relevant row for collisions*/
			if(z==board->boardMatrix[x][currCol][0])
				return 1;


	// check again if rows/cols & x/y match
	currRow=x-(x%BLOCK_SIZE_N);
	currCol=y-(y%BLOCK_SIZE_M);

	for(i=0;i<BLOCK_SIZE_N;i++)/*scan relevant block for collisions, starting top left corner.*/
		for(j=0;j<BLOCK_SIZE_M;j++)
			if(z==board->boardMatrix[currRow+i][currCol+j][0])
				return 1;

	return 0;
}



/* this is the full version with marking errorous cells in memory
int markErrors(GameBoard *board ,int z, int x, int y){
	int i,j,currRow,currCol, error=0;

	if(board->boardMatrix[x][y][1]==2){

	}

	for(currRow=0;currRow<BLOCK_SIZE_M;++currRow){ //scan relevant column for collisions
		if(z==board->boardMatrix[currRow][y][0]){
			if(board->boardMatrix[currRow][y][1]!=1)
				board->boardMatrix[currRow][y][1]=2;
		}
		isError=1;
	}


	for(currCol=0;currCol<BLOCK_SIZE_N;++currCol){//scan relevant row for collisions
			if(z==board->boardMatrix[x][currCol][0]){
				if(z==board->boardMatrix[x][currCol][1]!=1)
					board->boardMatrix[x][currCol][1]=2;
			}
		isError=1;
	}

	// check again if rows/cols & x/y match
	currRow=x-(x%BLOCK_SIZE_N);
	currCol=y-(y%BLOCK_SIZE_M);

	for(i=0;i<BLOCK_SIZE_N;i++){ //scan relevant block for collisions, starting top left corner.
		for(j=0;j<BLOCK_SIZE_M;j++){
			if(z==board->boardMatrix[currRow+i][currCol+j][0])
				if(board->boardMatrix[currRow+i][currCol+j][1]!=1)
					board->boardMatrix[currRow+i][currCol+j][1]=2;
		isError=1;
		}
	}


}

*/

int isFixed(int x, int y){
	return board.boardMatrix[x][y][1]==1;
}

int isError(int x, int y){
	return board.boardMatrix[x][y][1]==2;
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
	free(address);
	printf("Exiting...\n");
	}

int show_errors(){
	if(mark_errors==0&game_mode==1)
		return 0;
	else{ return 1}
}

/*
 * PRIVATE METHOMDS FOLLOW
 */


void printSeperatingDashes(){
	for(int i=0;i<(4*(BLOCK_SIZE_N+BLOCK_SIZE_M)+BLOCK_SIZE_N+1);i++)
		printf("-");
	printf("\n");
}



/*
 * print the game board
 */


void printBoard(GameBoard board){
	int i, j, k, l, x=0, y=0;

	for(k=0; k<BLOCK_SIZE_N; k++){
		printSeperatingDashes();
		for(l=0; l<BLOCK_SIZE_N; l++){
		for(i=0; i<BLOCK_SIZE_M; i++){
				printf("|");
				for(j=0; j<BLOCK_SIZE; j++){

					if(board.boardMatrix[x][y][1]==1)
						printf(".");
					if(show_errors() && hasError(&board,x,y))
						printf("*");
					else
						printf(" ");
					if(board.boardMatrix[x][y][0]==0)
						printf(" ");
					else
						printf("%2d",board.boardMatrix[x][y][0]);
					y++;
				}
							}
		printf("|\n");
		y=0;
		x++;
		}
	}
	printSeperatingDashes();
}


int isGameOver(){
	return (fullCells == (BLOCK_SIZE_N+BLOCK_SIZE_M)*(BLOCK_SIZE_N+BLOCK_SIZE_M));
}
/* copy the content of two gameboards
 * if func=0,funtion doesnt print diffs.
 * if func=1, function prints diffs for the undo funtion.
 * if func=2 function prints diffs for the redo funtion.
 */
void deepCopy(GameBoard *to, GameBoard *from, int func){
	int i,j;
	char *func_name;
	if(print==1)
		func_name="UNDO";
	if(print==2)
		func_name="REDO";

	for (i=0; i<(BLOCK_SIZE_N+BLOCK_SIZE_M); ++i){
		for (j=0; j<(BLOCK_SIZE_N+BLOCK_SIZE_M); ++j){
			if(func !=0 && to->boardMatrix[i][j][0] != from->boardMatrix[i][j][0])
				printf("%s %d,%d: from %d to %d\n", func_name, i,j, from->boardMatrix[i][j][0], to->boardMatrix[i][j][0])
			to->boardMatrix[i][j][0] = from->boardMatrix[i][j][0];

		}

	}
}

void initBoard(GameBoard *board){
	int i,j;

	for(i=0; i<TABLE_SIZE; ++i)
		for(j=0; j<TABLE_SIZE; ++j){
			board->boardMatrix[i][j][0]=0;
			board->boardMatrix[i][j][1]=0;
		}
}


