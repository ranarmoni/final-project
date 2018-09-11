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
int markErrors; /*0=no, 1=yes*/


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
				printf("in solve, address is %s\n",address);
				loadBoard(list);
				gameMode=1;
				break;

			case 2: /*edit*/
				loadBoard(list);
				gameMode=2;
				break;

			case 3: /*mark_errors X*/
				markErrors=command[1];
				break;

			case 4: /*print_board*/
				printBoard(list->curr->board);
				break;

			case 5: /*set X Y Z*/
				setCell(command[3], command[1], command[2], list);
				break;

			case 6: /*validate*/
				validateBoard(list->curr->board);
				break;

			case 7: /*generate X Y*/
				/*generateBoard(command[1],command[2]);*/
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
				printf("command recieved: %d, %d, %d",command[0],command[1],command[2]);
				hintCell(list->curr->board, command[1],command[2]);
				break;

			case 12: /*num_solutions*/
				/*numSolutions();*/
				break;

			case 13: /*autofill*/
				autofill(list);
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
		printf("free\n");


	}

	return 1;
}
