/*
 * contains all functions relevant to the game commands.
 * unless stated otherwise, functions return 1 upon finishing successfully.
 * detailed documentation follows.
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
#include <time.h>
#include <stdlib.h>


int fullCells;

/*
 * function declarations. see documentation in the code.
 */
int isFixed(GameBoard *board,int x,int y);
void deepCopy(GameBoard *to, GameBoard *from);
void initBoard(GameBoard *board);
int markErrorsInBoard(GameBoard *board);
int hasError(GameBoard *board ,int x, int y);
int loadBoard(ActionList *list,int solveMode);
int saveBoard(ActionList *list);
void markCellsAsFixed(GameBoard *board);
int isLegalSet(GameBoard *board ,int z, int x, int y);
int setCell(int z, int x, int y, ActionList *list);
int validateBoard(GameBoard *board, int printStatus);
int autofill(ActionList *list);
void exitCommand(ActionList *list);
void hintCell(GameBoard *board, int x,int y);
void generateBoard(GameBoard *board, int x, int y);
int numSolutions(GameBoard *board);
int markErrorsInCell(GameBoard *board ,int x, int y);
int cellHaslegalValue(GameBoard *board, int x,int y);
int scanErrorsInCell(GameBoard *board ,int x, int y, int z, int markCells);
void printSeperatingDashes();
int show_errors();



/*
 * print the game board according to instructions.
 * gets board pointer as parameter.
 */

void printBoard(GameBoard *board){
	int i, j, k, l, x=0, y=0;

	for(k=0; k<BLOCK_SIZE_N; k++){
		printSeperatingDashes();
		for(l=0; l<BLOCK_SIZE_M; l++){
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

/*
 *generates board according to instructions:
 *iterates 1000 times trying to randomly generate a valid board (checked by the gurobi mudule) with x numbers.
 *if succeeded - cells are deleted until y random cells are left in board.
 *gets board pointer as parameter.
 */

void generateBoard(GameBoard *board, int x, int y){
	int i,j,err,randVal,randX,randY, *boardMat=board->board;
	srand(time(NULL));
	for(i=0; i<1000; i++){
		err = 0;
		/* Initialize a board from scratch */
		free(boardMat);
		boardMat = (int*)calloc(TABLE_SIZE*TABLE_SIZE*3,sizeof(int));
		board->board = boardMat;
		/* choose x cells at random and fill them with some legal value, if no legal value exists for a cell, repeat the process*/
		for(j=0; j<x; j++){
			randX = rand()%TABLE_SIZE;
			randY = rand()%TABLE_SIZE;
			if(cellHaslegalValue(board ,randX,randY)){
				do{
					randVal = (rand()%TABLE_SIZE)+1;
				} while(!isLegalSet(board ,randVal,randX,randY));
				boardMat[calcIndex(randX,randY,0,TABLE_SIZE,3)] = randVal;
			}
			else{
				err = 1;
				break;
			}
		}
		if(!err){
			/* if a legal placement was found, try and solve the board with ILP, if failed repeat the process */
			if(ILPsolve(board,board)==1){
				for(j=0; j<(TABLE_SIZE*TABLE_SIZE-y); j++){
					randX = rand()%TABLE_SIZE;
					randY = rand()%TABLE_SIZE;
					if(board->board[calcIndex(randX,randY,0,TABLE_SIZE,3)] != 0)
						board->board[calcIndex(randX,randY,0,TABLE_SIZE,3)] = 0;
					else
						j--;
				}
				fullCells = y;
				printBoard(board);
				return;
			}
		}
	}
	free(board->board);
	board->board = (int*)calloc(TABLE_SIZE*TABLE_SIZE*3,sizeof(int));
	if(!board->board){
		printf("Error: calloc has failed\n");
		exit(0);
	}
	printf("Error: puzzle generator failed\n");
}

/*returns 1 if cell x,y has a possible legal value using "isLegalSet", 0 otherwise.
 * gets board pointer as parameter.
 */

int cellHaslegalValue(GameBoard *board, int x,int y){
	int i;

	for(i=1; i<=TABLE_SIZE; i++){
		if(isLegalSet(board,i, x, y))
			return 1;
	}
	return 0;
}



/*set the markErrors field to 0 or 1 (supplied as val)*/
void setMarkErrors(int val){
	markErrors=val;
}

/*
 * load board from file or generate an empty 9*9 board, according to input.
 * file address taken from the "address" global field.
 * cleans the action list (pointer supplied) and places the new board in the first node of the cleaned action list.
 *uses the loadFile function from IO module
 */

 /* places the new board in the current node of the action list which is supplied as a parameter.
 *uses the loadFile function from IO module */
int loadBoard(ActionList *list, int solveMode){
	GameBoard dummyboard;
	if(loadFile(address, &dummyboard, 0)==0){
		if(strcmp(address,"")==0){
			cleanList(list);
			BLOCK_SIZE_N = 3;
			BLOCK_SIZE_M = 3;
			TABLE_SIZE = 9;
			fullCells = 0;
			list->first->board->board = (int*)calloc(3*TABLE_SIZE*TABLE_SIZE,sizeof(int));
			if(!list->first->board->board){
				printf("Error: calloc has failed\n");
				exit(0);
			}

		}
		else{
			if(solveMode)
				printf("Error: File doesn't exist or cannot be opened\n");
			else
				printf("Error: File cannot be opened\n");
			return 0;
		}
	}
	else{
		free(dummyboard.board);
		cleanList(list);
		loadFile(address, list->curr->board, solveMode);
	}
	return 1;
}

/*saves board to file.
 *file address taken from the "address" global field.
 *file the board is taken from the current node of the action list, which is supplied as a parameter.
 *uses the saveFile function from IO module*/

int saveBoard(ActionList *list){
	if(gameMode==2){
		if(markErrorsInBoard(list->curr->board)){
			printf("Error: board contains erroneous values\n");
			return 0;
		}
		if(!validateBoard(list->curr->board,0)){
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

/*marks all cells as fixed, as needed before saving a file in edit mode.*/

 void markCellsAsFixed(GameBoard *board){
	int i;
	for(i=0;i<TABLE_SIZE*TABLE_SIZE;i++){
		if(board->board[i*3]!=0)
			board->board[i*3+1]=1;
	}
}

 /*set cell X,Y to Z
  * Receives the list as parameter.
  * changes the board in the "current" node of the list.
  * adds a new node if a change is made.
  * upon finishing, prints board and calls the isGameOver function that handles the game over scenario if needed.
  */

int setCell(int z, int x, int y, ActionList *list){
	int currVal = list->curr->board->board[calcIndex(x-1,y-1,0,TABLE_SIZE,3)];
	if(isFixed(list->curr->board,x-1,y-1)){
			printf("Error: cell is fixed\n");
			return 0;
		}
	if(z==0&&currVal!=0)
		fullCells--;
	if(z!=0&&currVal==0)
		fullCells++;
	if(list->curr->board->board[calcIndex(x-1,y-1,0,TABLE_SIZE,3)] != z)
		addNewNode(list);
	list->curr->board->board[calcIndex(x-1,y-1,0,TABLE_SIZE,3)]=z;
	markErrorsInBoard(list->curr->board);
	printBoard(list->curr->board);
	if(isGameOver(list->curr->board))
		return 1;

	return 1;
}

/*
 * checks if the game is over, prints relevant message, changes mode to "init" if finished properly.
 */

int isGameOver(GameBoard *board){
	if(fullCells==TABLE_SIZE*TABLE_SIZE && gameMode==1){
			if(markErrorsInBoard(board)){
				printf("Puzzle solution erroneous\n");
				return 1;
			}
			printf("Puzzle solved successfully\n");
			gameMode=0;
			return 0;
		}
	return 0;
}

/*
 * gets list pointer as parameter. generates a copy of the current board, then scans cells for trivial fills.
 * if found - they are written into the copy of the board and proper message is printed.
 * after board is scanned fully - if any changes were made, a new node in the action list is created, and the new board is copied into it.
 */


int autofill(ActionList *list){
	int i, val, possibleVal, valCount, j, isChanged;
	GameBoard *newBoard = (GameBoard*)calloc(1,sizeof(GameBoard));
	newBoard->board = (int*)calloc(3*TABLE_SIZE*TABLE_SIZE,sizeof(int));
	possibleVal=0;
	isChanged=0;

	if(!newBoard || !newBoard->board){
		printf("Error: calloc has failed\n");
		exit(0);
	}

	memcpy(newBoard->board,list->curr->board->board,TABLE_SIZE*TABLE_SIZE*3*sizeof(int));
	for(i=0;i<TABLE_SIZE;i++){
		for(j=0;j<TABLE_SIZE;j++){
			if(list->curr->board->board[calcIndex(i,j,0,TABLE_SIZE,3)]==0){
				valCount=0;
				for(val=1;val<=TABLE_SIZE;val++){
					if(isLegalSet(list->curr->board ,val, i, j)){
						if(valCount>0){
							valCount++;
							}
						else{
							possibleVal=val;
							valCount++;
						}
					}
				}
				if(valCount==1){
					newBoard->board[calcIndex(i,j,0,TABLE_SIZE,3)]=possibleVal;
					fullCells++;
					isChanged=1;
					printf("Cell <%d,%d> set to %d\n",j+1,i+1,possibleVal);
				}
			}

		}

	}

	if(isChanged){
		addNewNode(list);
		memcpy(list->curr->board->board,newBoard->board,TABLE_SIZE*TABLE_SIZE*3*sizeof(int));
	}

	printBoard(list->curr->board);
	free(newBoard->board);
	free(newBoard);
	isGameOver(list->curr->board);
	return 1;
}

/*
 * scans cell X,Y for errors.
 * if parameter markCells==1, the errors found are marked. else, errors aren't marked.
 * z parameter optional. if 0 - the current value in cell is checked.
 * if z supplied - function checks whether z in cell x,y is legal.
 */

int scanErrorsInCell(GameBoard *board ,int x, int y, int z, int markCells){
	int i,j,currRow,currCol, hasError=0;

	if(z==0)
		z=board->board[calcIndex(x,y,0,TABLE_SIZE,3)];


	for(currRow=0;currRow<TABLE_SIZE;++currRow) /*scan relevant column for collisions*/

		if(z==board->board[calcIndex(currRow,y,0,TABLE_SIZE,3)]&&currRow!=x&&z!=0){
			if(markCells)
				board->board[calcIndex(currRow,y,2,TABLE_SIZE,3)]=1;
			hasError=1;
		}

	for(currCol=0;currCol<TABLE_SIZE;++currCol)/*scan relevant row for collisions*/
		if(z==board->board[calcIndex(x,currCol,0,TABLE_SIZE,3)]&&currCol!=y&&z!=0){
			if(markCells)
				board->board[calcIndex(x,currCol,2,TABLE_SIZE,3)]=1;
			hasError=1;
			}


	currRow=x-(x%BLOCK_SIZE_M);
	currCol=y-(y%BLOCK_SIZE_N);

	for(i=0;i<BLOCK_SIZE_M;i++)/*scan relevant block for collisions, starting top left corner.*/
		for(j=0;j<BLOCK_SIZE_N;j++)
			if(z==board->board[calcIndex(currRow+i,currCol+j,0,TABLE_SIZE,3)]&&z!=0&&(currRow+i!=x || currCol+j!=y)){
				if(markCells)
					board->board[calcIndex(currRow+i,currCol+j,2,TABLE_SIZE,3)]=1;
				hasError=1;
			}

	if(markCells)
		board->board[calcIndex(x,y,2,TABLE_SIZE,3)]=hasError;
	return hasError;
}




/*
 * marks errors in cell x,y, and in other cells that "participate" in errors with x,y.
 * uses scanErrorsInCell with z=0 (in order for current value to be checked) and markCells=1.
 */

int markErrorsInCell(GameBoard *board ,int x, int y){
	return scanErrorsInCell(board,x,y,0,1);
}



/*
 * checks whether z is a legal set to X,Y. returns 1 if legal, 0 otherwise.
 * uses scanErrorsInCell with markCells=0 ("theoretical" errors doesn't need to be marked).
 * used by the autofill method and backtracking module.
 * a pointer to board is supplied as a parameter.
 */

int isLegalSet(GameBoard *board ,int z, int x, int y){

	return !scanErrorsInCell(board,x,y,z,0);

}


/*
 * marks errors in the whole board by running markErrorsInCell on all the cells.
 *returns 1 if board has errors, 0 otherwise.
 */

int markErrorsInBoard(GameBoard *board){
	int i,j,hasErrors=0;
	for(i=0;i<TABLE_SIZE;i++)
		for(j=0;j<TABLE_SIZE;j++)
			if(markErrorsInCell(board,i,j))
				hasErrors=1;
	return hasErrors;
}



/*returns 1 if a cell is marked as fixed, 0 otherwise*/

int isFixed(GameBoard *board, int x, int y){
	return (int)(board->board[calcIndex(x,y,1,TABLE_SIZE,3)]==1);
}

/*returns 1 if a cell is marked as error, 0 otherwise*/

int isError(GameBoard *board,int x, int y){
	return (int)(board->board[calcIndex(x,y,1,TABLE_SIZE,3)]==2);
}

/*
 * provides a hint for cell X,Y by generating a solution using the gurobi solver.
 * board pointer supplied as parameter.
 */

void hintCell(GameBoard *board,int x,int y){
	int err;
	GameBoard solution;

	if(markErrorsInBoard(board))
		printf("Error: board contains erroneous values\n");
	else if(board->board[calcIndex(x-1,y-1,1,TABLE_SIZE,3)]==1)
		printf("Error: cell is fixed\n");
	else if(board->board[calcIndex(x-1,y-1,0,TABLE_SIZE,3)]!=0)
		printf("Error: cell already contains a value\n");
	else{
		solution.board = (int*)calloc(TABLE_SIZE*TABLE_SIZE*3,sizeof(int));

		if(!solution.board){
			printf("Error: calloc has failed\n");
			exit(0);
		}

		err = ILPsolve(board, &solution);
		if(err == -1){
			printf("Gurobi has failed\n");
			exit(0);
		}
		if(err == 0)
			printf("Error: board is unsolvable\n");
		else
			printf("Hint: set cell to %d\n",solution.board[calcIndex(x-1,y-1,0,TABLE_SIZE,3)]);
		free(solution.board);
	}
}

/*
 * checks whether the board is solvable by trying to solve it with the gurobi module.
 * if printStatus==1, function print relevant messages (for the validate game call).
 * else - function doesn't print, happens when validate is used before save.
 * board pointer supplied as parameter.
 */

int validateBoard(GameBoard *board, int printStatus){
	GameBoard sol;
	int ret;
	sol.board = (int*)calloc(TABLE_SIZE*TABLE_SIZE*3,sizeof(int));

	if(!sol.board){
		printf("Error: calloc has failed\n");
		exit(0);
	}

	if(markErrorsInBoard(board)){
		if(printStatus)
			printf("Error: board contains erroneous values\n");
		ret = 0;
	}
	else if (ILPsolve(board,&sol)){
		if(printStatus)
			printf("Validation passed: board is solvable\n");
		ret = 1;
	}
	else{
		if(printStatus)
			printf("Validation failed: board is unsolvable");
		ret = 0;
	}
	free(sol.board);
	return ret;
}


/*
 * free list and print exit message.
 */

void exitCommand(ActionList *list){
	freeList(list);
	printf("Exiting...\n");
	}





/*counts possible solutions using the countNumberOfSols method from "solver" module*/

 int numSolutions(GameBoard *board){
	int solCount;

	if(markErrorsInBoard(board)){
		printf("Error: board contains erroneous values\n");
		return 0;
	}
	solCount = countNumberOfSols(board);
	printf("Number of solutions: %d\n",solCount);
	if(solCount == 1)
		printf("This is a good board!\n");
	else if (solCount > 1)
		printf("The puzzle has more than 1 solution, try to edit it further\n");
	return 1;

}


/*
 * PRIVATE METHOMDS FOLLOW
 */

/*prints a row of dashes, used by print method*/

void printSeperatingDashes(){
	int i;
	for(i=0;i<(4*(BLOCK_SIZE_N*BLOCK_SIZE_M)+BLOCK_SIZE_M+1);i++)
		printf("-");
	printf("\n");
}

/*
 * used by print, returns 0 if mode is solve and mark_errors is false, 1 otherwise.
 */

int show_errors(){
	if(markErrors==0 && gameMode==1){
		return 0;
	}
	return 1;
}


