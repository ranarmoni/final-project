/*#include "parser.h"
*/
#include "game.h"
#include <stdio.h>
#include "solver.h"
#include "parser.h"
#include "ActionList.h"
#include "MainAux.h"
#include "fileIO.h"
#include <string.h>
#include "grb_solver.h"


ActionList actionList;
int fixedAmnt;
int fullCells;

/*
 * checks whether cell (x,y) is fixed.
 */
int isFixed(GameBoard *board,int x,int y);
/*
 * creates a deep copy of the game board.
 */
void deepCopy(GameBoard *to, GameBoard *from);
void initBoard(GameBoard *board);
int boardHasError(GameBoard *board);
int hasError(GameBoard *board ,int x, int y);
void loadBoard(ActionList *list);
int saveBoard(ActionList *list);
void markCellsAsFixed(GameBoard *board);
int isLegalSet(GameBoard *board ,int z, int x, int y);
int setCell(int z, int x, int y, ActionList *list);
int validateBoard(GameBoard *board);
int autofill(ActionList *list);
void exitCommand(ActionList *list);
void hintCell(GameBoard *board, int x,int y);
void generateBoard(GameBoard *board, int x, int y);
int numSolutions();
int markErrorsInBoard(GameBoard *board);
int markErrorsInCell(GameBoard *board ,int x, int y);




int startGame(){

	return 1;
}


void loadBoard(ActionList *list){
	if(loadFile(address, list->curr->board)==0){
		if(strcmp(address,"")==0){
			cleanList(list);
			BLOCK_SIZE_N = 3;
			BLOCK_SIZE_M = 3;
			TABLE_SIZE = 9;
			list->first->board->board = (int*)calloc(3*TABLE_SIZE*TABLE_SIZE,sizeof(int));
		}
		else{
			printf("Error: File doesn't exist or cannot be opened\n");
		}
	}
	else{
		cleanList(list);
		loadFile(address, list->curr->board);
	}
}

int saveBoard(ActionList *list){
	if(gameMode==2){
		if(boardHasError(list->curr->board)){
			printf("Error: board contains erroneous values\n");
			return 0;
		}
		if(!validateBoard(list->curr->board)){
			printf("Error: board validation failed\n");
			return 0;
		}
		markCellsAsFixed(list->curr->board);
	}
	if(!saveFile(address, list->curr->board)){
		printf("Error: File cannot be created or modified\n");
		return 0;
	}
	printf("Saved to: %s\n", address);
	return 1;


}

void markCellsAsFixed(GameBoard *board){
	int i;
	for(i=0;i<TABLE_SIZE*TABLE_SIZE;i++){
		if(board->board[i*3]!=0)
			board->board[i*3+1]=1;
	}
}


int setCell(int z, int x, int y, ActionList *list){
	addNewNode(list);

	if(isFixed(list->curr->board,x-1,y-1)){
		printf("Error: cell is fixed\n");
		return 0;
	}

	list->curr->board->board[calcIndex(x-1,y-1,0,TABLE_SIZE,3)]=z;
	markErrorsInBoard(list->curr->board);
	fullCells++;
	printBoard(list->curr->board);
	if(fullCells==TABLE_SIZE*TABLE_SIZE){
		if(boardHasError(list->curr->board)){
			printf("Puzzle solution erroneous\n");
			return 1;
		}
		printf("Puzzle solved successfully\n");
		gameMode=0;
	}

	return 1;
}


int isLegalSet(GameBoard *board ,int z, int x, int y){
	int i,j,currRow,currCol;


	for(currRow=0;currRow<TABLE_SIZE;++currRow) /* scan relevant column for collisions */
		if(z==board->board[calcIndex(currRow,y,0,TABLE_SIZE,3)])
			return 0;

	for(currCol=0;currCol<TABLE_SIZE;++currCol) /* scan relevant row for collisions */
			if(z==board->board[calcIndex(x,currCol,0,TABLE_SIZE,3)])
				return 0;


	/* check again if rows/cols & x/y match */
	currRow=x-(x%BLOCK_SIZE_N);
	currCol=y-(y%BLOCK_SIZE_M);

	for(i=0;i<BLOCK_SIZE_N;i++) /* scan relevant block for collisions, starting top left corner. */
		for(j=0;j<BLOCK_SIZE_M;j++)
			if(z==board->board[calcIndex(currRow+i,currCol+j,0,TABLE_SIZE,3)])
				return 0;

	return 1;
}



int boardHasError(GameBoard *board){
	int i,j,N=BLOCK_SIZE_N*BLOCK_SIZE_M;
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			if(hasError(board,i,j))
				return 1;
	return 0;
	return markErrorsInBoard(board);
}

int markErrorsInBoard(GameBoard *board){
	int i,j,hasErrors=0;
	for(i=0;i<TABLE_SIZE;i++)
		for(j=0;j<TABLE_SIZE;j++)
			if(markErrorsInCell(board,i,j))
				hasErrors=1;
	return hasErrors;
}


int autofill(ActionList *list){
	int i, val, possibleVal, writeVal, j;
	GameBoard *newBoard = (GameBoard*)calloc(1,sizeof(GameBoard));
	newBoard->board = (int*)calloc(3*TABLE_SIZE*TABLE_SIZE,sizeof(int));
	addNewNode(list);
	memcpy(newBoard->board,list->curr->board->board,TABLE_SIZE*TABLE_SIZE*3*sizeof(int));
	for(i=0;i<BLOCK_SIZE_N;i++){
		for(j=0;j<BLOCK_SIZE_M;j++){
			if(list->curr->board->board[calcIndex(i,j,0,TABLE_SIZE,3)]==0){
				writeVal=0;
				for(val=0;val<TABLE_SIZE;val++){
					if(isLegalSet(list->curr->board ,val, i, j)){
						if(writeVal){
							writeVal=0;
							break;
						}
						else{
							possibleVal=val;
							writeVal=1;
						}
					}
				}
				if(writeVal)
					newBoard->board[calcIndex(i,j,0,TABLE_SIZE,3)]=possibleVal;
			}
		}
	}
	list->curr->board=newBoard;
	return 1;
}



int markErrorsInCell(GameBoard *board ,int x, int y){
	int i,j,currRow,currCol,z, hasError=0;
	z=board->board[calcIndex(x,y,0,TABLE_SIZE,3)];


	for(currRow=0;currRow<BLOCK_SIZE_M;++currRow) /*scan relevant column for collisions*/

		if(z==board->board[calcIndex(currRow,y,0,TABLE_SIZE,3)]&&currRow!=x&&z!=0){
			board->board[calcIndex(currRow,y,2,TABLE_SIZE,3)]=1;
			hasError=1;
		}

	for(currCol=0;currCol<BLOCK_SIZE_N;++currCol)/*scan relevant row for collisions*/
		if(z==board->board[calcIndex(x,currCol,0,TABLE_SIZE,3)]&&currCol!=y&&z!=0){
			board->board[calcIndex(x,currCol,2,TABLE_SIZE,3)]=1;
			hasError=1;
			}

	/* check again if rows/cols & x/y match */
	currRow=x-(x%BLOCK_SIZE_N);
	currCol=y-(y%BLOCK_SIZE_M);

	for(i=0;i<BLOCK_SIZE_N;i++)/*scan relevant block for collisions, starting top left corner.*/
		for(j=0;j<BLOCK_SIZE_M;j++)
			if(z==board->board[calcIndex(currRow+i,currCol+j,0,TABLE_SIZE,3)]&&z!=0&&(currRow+i!=x || currCol+j!=y)){
				board->board[calcIndex(currRow+i,currCol+j,2,TABLE_SIZE,3)]=1;
				hasError=1;
			}
	board->board[calcIndex(x,y,2,TABLE_SIZE,3)]=hasError;
	return hasError;
}

int hasError(GameBoard *board ,int x, int y){
	return markErrorsInCell(board,x,y);
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

int isFixed(GameBoard *board, int x, int y){
	return (int)(board->board[calcIndex(x,y,1,TABLE_SIZE,3)]==1);
}

int isError(GameBoard *board,int x, int y){
	return (int)(board->board[calcIndex(x,y,1,TABLE_SIZE,3)]==2);
}


void hintCell(GameBoard *board,int x,int y){
	int err;
	GameBoard solution;
	if(boardHasError(board))
		printf("Error: board contains erroneous values\n");
	else if(board->board[calcIndex(x-1,y-1,1,TABLE_SIZE,3)]==1)
		printf("Error: cell is fixed\n");
	else if(board->board[calcIndex(x-1,y-1,0,TABLE_SIZE,3)]!=0)
		printf("Error: cell already contains a value\n");
	else{
		solution.board = (int*)calloc(TABLE_SIZE*TABLE_SIZE*3,sizeof(int));
		err = ILPsolve(board, &solution);
		if(err == -1){
			printf("Gurobi has failed");
			exit(0);
		}
		if(err == 0)
			printf("Error: board is unsolvable\n");
		else
			printf("Hint: set cell to %d",board->board[calcIndex(x-1,y-1,0,TABLE_SIZE,3)]);
		free(solution.board);
	}
}


/* NEEDS TO RETURN INT (0=not valid, 1=valid)*/
int validateBoard(GameBoard *board){
	board=board;
	/*
	GameBoard newSol, *temp;
	deepCopy(&newSol, &board);
	temp = hasSolution(&newSol);
	if (temp != NULL){
		solution = *temp;
		printf("Validation passed: board is solvable\n");
		return 1;
	}
	else
		printf("Validation failed: board is unsolvable\n");
		*/
		return 0;
}


/*
 * free space
 * close everything
 */

void exitCommand(ActionList *list){
	freeList(list);
	printf("Exiting...\n");
	exit(1);
	}

int show_errors(){
	if(markErrors==0 && gameMode==1){
		return 0;
	}
	return 1;
}

/*
 * PRIVATE METHOMDS FOLLOW
 */


void printSeperatingDashes(){
	int i;
	for(i=0;i<(4*(BLOCK_SIZE_N*BLOCK_SIZE_M)+BLOCK_SIZE_M+1);i++)
		printf("-");
	printf("\n");
}



/*
 * print the game board
 */


void printBoard(GameBoard *board){
	int i, j, k, l, x=0, y=0;

	for(k=0; k<BLOCK_SIZE_N; k++){
		printSeperatingDashes();
		for(l=0; l<BLOCK_SIZE_N; l++){
		for(i=0; i<BLOCK_SIZE_M; i++){
				printf("|");
				for(j=0; j<BLOCK_SIZE_N; j++){
					printf(" ");
					if(board->board[calcIndex(x,y,0,TABLE_SIZE,3)]==0)
						printf("   ");
					else{
						printf("%2d",board->board[calcIndex(x,y,0,TABLE_SIZE,3)]);
						if(board->board[calcIndex(x,y,1,TABLE_SIZE,3)]==1)
							printf(".");
						else{
							if(show_errors() && board->board[calcIndex(x,y,2,TABLE_SIZE,3)]==1)
								printf("*");
							else
								printf(" ");
					}
					}


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

void generateBoard(GameBoard *board, int x, int y){

}

/* copy the content of two gameboards
 * if func=0,funtion doesnt print diffs.
 * if func=1, function prints diffs for the undo funtion.
 * if func=2 function prints diffs for the redo funtion.
 */

/*
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

*/
/*
void initBoard(GameBoard *board){
	int i,j;

	for(i=0; i<TABLE_SIZE; ++i)
		for(j=0; j<TABLE_SIZE; ++j){
			board->boardMatrix[i][j][0]=0;
			board->boardMatrix[i][j][1]=0;
		}
}
*/

