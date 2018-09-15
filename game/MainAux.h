/*
 auxiliary functions.
 holds only the calcindex function that translates board coordinates to array coordinate.
 */

#include "game.h"



#ifndef MAINAUX_H_
#define MAINAUX_H_

#include "game.h"

/*
 * the function translates board coordinates to array coordinate.
 * X,Y,Z are the coordinates to be translated (z=0 is value,z=1 is fixed mark, z=2 is error mark).
 * d1 is the table size (n*m), and d2 is the size of z dimension - usually 3)
 * function return the correct array coordinate.
 */
int calcIndex(int x, int y, int z,int d1, int d2);


#endif /* MAINAUX_H_ */
