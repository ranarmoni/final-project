/*
 * game.h
 *
 *  Created on: 17 May 2018
 *      Author: hp envy
 */

#ifndef GAME_H_
#define GAME_H_



extern int BLOCK_SIZE_N;
extern int BLOCK_SIZE_M;
extern int TABLE_SIZE; /* =N*M */
extern char address[256];

/*#include "parser.h"*/


int gameMode; /* 0=init, 1=solve, 2=edit */
int markErrors; /*0=no, 1=yes*/


typedef struct gameBoardStruct{
	int* board;
} GameBoard;

struct Node {
	GameBoard *board;
	struct Node* next;
	struct Node* prev;
};

typedef struct Node Node;

struct ActionList{
	Node *curr;
	Node *first;
};


typedef struct ActionList ActionList;




/* initialization function. recieves fixed cells amount using parser,
 * calls the generation functions of solver.h, stores board and solution, and prints board*/
int startGame();

/*
 * set value z to cell (x,y). calls private functions that validates that set is legal.
 */
int setCell(int z, int x, int y, ActionList *list);
/*
 * give hint in cell (x,y) from stord solution.
 */
void hintCell(int x,int y);

/*
 * return if the board is solveable or not using the relevant function of solver.h,
 *  and stores the new solution supplied by it.
 */
int validateBoard(GameBoard *board);
/*
 * a.	Restart the game by calling startGame()
 */
void restartGame();

/*
 * free space
 * close everything
  */
void exitCommand();

/*
 * prints gameboard
 */
void printBoard(GameBoard *board);

/*
 * checks whether game is over (there are 81 full cells).
 */
int isGameOver();

/*
 * checks if z is a valid number for cell (x,y).
 */
int isLegalSet(GameBoard *board ,int z, int x, int y);

/*
 * get amount of empty cells in the current boardד
 */
int getEmptyCells();


void loadBoard(ActionList *list);
int saveBoard(ActionList *list);
int isLegalSet(GameBoard *board ,int z, int x, int y);
int validateBoard(GameBoard *board);
int autofill(ActionList *list);
void exitCommand(ActionList *list);


#endif /* GAME_H_ */
