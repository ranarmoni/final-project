/*
 * grb_solver.c
 *
 *  Created on: 26 Aug. 2018
 *      Author: hp envy
 */

#include "gurobi_c.h"
#include "game.h"
#include "grb_solver.h"

GameBoard* solve(GameBoard board){
	GRBenv   *env   = NULL;
	GRBmodel *model = NULL;
	int       error = 0;

}
