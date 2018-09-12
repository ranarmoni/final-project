#include "game.h"
#include "solver.h"
#include "parser.h"
#include "ActionList.h"
#include "grb_solver.h"
#include "fileIO.h"
#include <string.h>

#include <stdio.h>

#define true 1

int BLOCK_SIZE_N=3;
int BLOCK_SIZE_M=3;
int TABLE_SIZE=9;
int fullCells;
int gameMode; /* 0=init, 1=solve, 2=edit */
int markErrors=1; /*0=no, 1=yes*/

int main(){
	GameBoard board;
	ActionList *list;
	/*board.board = calloc(TABLE_SIZE*TABLE_SIZE*3,sizeof(int));*/
	list = (ActionList*)calloc(1,sizeof(ActionList));
	initList(list);
	memcpy(address,"sample.sud",10);
	
	loadBoard(list);
	setCell(1, 1, 1, list);
	
	free(board.board);
	freeList(list);
	return 1;
}
