/*
 * game.h
 *
 *  Created on: 17 May 2018
 *      Author: hp envy
 */

#ifndef GAME_H_
#define GAME_H_

#define TABLE_SIZE 9
#define BLOCK_SIZE 3

/*#include "parser.h"*/

typedef struct gameBoardStruct{
	int boardMatrix[TABLE_SIZE][TABLE_SIZE][2];
} GameBoard;


/* initialization function. recieves fixed cells amount using parser,
 * calls the generation functions of solver.h, stores board and solution, and prints board*/
int startGame();

/*
 * set value z to cell (x,y). calls private functions that validates that set is legal.
 */
int setCell(int z, int x, int y);

/*
 * give hint in cell (x,y) from stord solution.
 */
void hintCell(int x,int y);

/*
 * return if the board is solveable or not using the relevant function of solver.h,
 *  and stores the new solution supplied by it.
 */
void validateBoard();

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
void printBoard(GameBoard board);

/*
 * checks whether game is over (there are 81 full cells).
 */
int isGameOver();

/*
 * checks if z is a valid number for cell (x,y).
 */
int isLegalSet(GameBoard *board ,int z, int x, int y);

#endif /* GAME_H_ */
