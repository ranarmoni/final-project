#include "game.h"
#include "solver.h"
#include "parser.h"
#include "ActionList.h"

#include <stdio.h>

#define true 1

int BLOCK_SIZE_N;
int BLOCK_SIZE_M;
int TABLE_SIZE;
int fullCells;
int gameMode; /* 0=init, 1=solve, 2=edit */
int markErrors=1; /*0=no, 1=yes*/


int main(){
	/* do first */
	int *command,exitStatus = 0;
	ActionList *list;
	printf("Sudoku\n------\n");
	gameMode = 0;
	list = (ActionList*)calloc(1,sizeof(ActionList));
	initList(list);
	while(exitStatus==0){

		command = readCommand();

		switch(command[0]){

			case 1: /*solve*/
				if(loadBoard(list,1)){
					gameMode=1;
					markErrorsInBoard(list->curr->board);
					printBoard(list->curr->board);
				}
				break;

			case 2: /*edit*/
				if(loadBoard(list,0)){
					gameMode=2;
					markErrorsInBoard(list->curr->board);
					printBoard(list->curr->board);
				}
				break;

			case 3: /*mark_errors X*/
				setMarkErrors(command[1]);
				break;

			case 4: /*print_board*/
				printBoard(list->curr->board);
				break;

			case 5: /*set X Y Z*/
				setCell(command[3], command[2], command[1], list);
				break;

			case 6: /*validate*/
				validateBoard(list->curr->board, 1);
				break;

			case 7: /*generate X Y*/
				if (fullCells == 0){
					if(command[2] != 0)
						addNewNode(list);
					generateBoard(list->curr->board, command[1],command[2]);
				}
				else
					printf("Error: board is not empty\n");
				break;

			case 8: /*undo*/
				undo(list);
				break;

			case 9: /*redo*/
				redo(list);
				break;

			case 10: /*save X*/
				saveBoard(list);
				break;

			case 11: /*hint X Y*/
				hintCell(list->curr->board, command[2],command[1]);
				break;

			case 12: /*num_solutions*/
				numSolutions(list->curr->board);
				break;

			case 13: /*autofill*/
				if(!markErrorsInBoard(list->curr->board))
					autofill(list);
				else
					printf("Error: board contains erroneous values\n");
				break;

			case 14: /*reset*/
				reset(list);
				break;

			case 15: /*exit*/
				exitCommand(list);
				exitStatus = 1;
				break;
		}
		free(command);

	}
	return 1;
}
