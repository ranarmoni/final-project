/*
 * solver.h
 *
 *  Created on: 17 May 2018
 *      Author: hp envy
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "game.h"
#include <time.h>
#include <stdlib.h>

/*
 * seed to be set by main for randomization
 */
void setSeed();



GameBoard* generateSolution(GameBoard *board);

/*
 * we need to make sure that fixed it is initialized to 0 unless really fixed
 */
GameBoard* generateBoard(GameBoard *solution, GameBoard *board, int fixedAmnt);


/*
 * function needs to supply new solution + print appropriate message.
 */
GameBoard* hasSolution(GameBoard *board);




/*
 * PRIVATE METHOMDS FOLLOW
 */



#endif /* SOLVER_H_ */
