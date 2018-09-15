/*
 * this module contains the exaustive backtracking solver.
 * its only interface is the function countNumberOfSols, desctiption below
 */

#ifndef SOLVER_H_
#define SOLVER_H_

/*
 * countNumberOfSols receives a single GameBoard type argument and counts
 * the number of possible solutions for it.
 * the function returns the number of possible solutions and prints this
 *  number to stdout followed by suggestive prints to the user according to instructions
 */

int countNumberOfSols(GameBoard *originalBoard);



#endif /* SOLVER_H_ */
