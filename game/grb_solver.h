/*
 * this module contains the ILPsolver, and can find a solution to a board very quickly
 */

#ifndef GRB_SOLVER_H_
#define GRB_SOLVER_H_

/*
 * solve the board supplied by the argument board and outputs the solution in solutionBoard
 * the function uses ILP (integer linear programming) with the gurobi module to solve the board
 * so gurobi must be installed and active for the function to work properly
 * the function returns 1 if a solution was found, 0 if none is found and -1 if a gurobi action has failed.
 */
int ILPsolve(GameBoard *board, GameBoard *solutionBoard);



#endif /* GRB_SOLVER_H_ */
