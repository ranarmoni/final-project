/*
 * grb_solver.c
 *
 *  Created on: 26 Aug. 2018
 *      Author: hp envy
 */

#include "game.h"
#include "grb_solver.h"
#include "MainAux.h"
#include "gurobi_c.h"
#include <stdio.h>
#include <stdlib.h>

int BLOCK_SIZE_N;
int BLOCK_SIZE_M;
int TABLE_SIZE;

int ILPsolve(GameBoard *board, GameBoard *solutionBoard){
	GRBenv   *env   = NULL;
	GRBmodel *model = NULL;
	int i, j, v, block_i, block_j, count, optimstatus, ret,
		n = BLOCK_SIZE_N, m = BLOCK_SIZE_M, nm = TABLE_SIZE, error = 0,
		*ind = (int*)calloc(nm,sizeof(int));
	double 	*initVals = (double*)calloc(nm*nm*nm,sizeof(double)),
			*val = (double*)calloc(nm,sizeof(double)),
			*sol = (double*)calloc(nm*nm*nm,sizeof(double)),
			objval;
	char *vtype = (char*)calloc(nm*nm*nm,sizeof(char));

	if(!ind || !initVals || !val || !sol || !vtype){
		printf("Error: calloc has failed\n");
		exit(0);
	}


	for (i = 0; i < nm; i++) {
	    for (j = 0; j < nm; j++) {
	    	for (v = 0; v < nm; v++) {
	    		if (board->board[calcIndex(i,j,0,nm,3)]-1 == v){
	    			initVals[calcIndex(i,j,v,nm,nm)] = 1.0;
	    			printf("found %d in index %d,%d\n",v,i,j);
	    		}
	    		else
	    			initVals[calcIndex(i,j,v,nm,nm)] = 0.0;
	    		vtype[calcIndex(i,j,v,nm,nm)] = GRB_BINARY;
	    	}
	    }
	}

	error = GRBloadenv(&env, "sudoku.log");
	if (error) {
		printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
		return -1;
	}

	error = GRBnewmodel(env, &model, "sudoku", nm*nm*nm, NULL, initVals, NULL, vtype, NULL);
	if (error) {
		printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
		return -1;
	}


	/* no empty cell constraint */

	for (i = 0; i < nm; i++) {
	    for (j = 0; j < nm; j++) {
	      for (v = 0; v < nm; v++) {
	        ind[v] = calcIndex(i,j,v,nm,nm);
	        val[v] = 1.0;
	      }

	      error = GRBaddconstr(model, nm, ind, val, GRB_EQUAL, 1.0, NULL);
			if (error) {
				printf("ERROR %d GRBaddconstr() - cell constraint: %s\n", error, GRBgeterrormsg(env));
				return -1;
			}
	    }
	}

	/* row constraint */

	for (v = 0; v < nm; v++) {
	    for (j = 0; j < nm; j++) {
	    	for (i = 0; i < nm; i++) {
	    		ind[i] = calcIndex(i,j,v,nm,nm);
	    		val[i] = 1.0;
	    	}

	    	error = GRBaddconstr(model, nm, ind, val, GRB_EQUAL, 1.0, NULL);
			if (error) {
				printf("ERROR %d GRBaddconstr() - row constraint: %s\n", error, GRBgeterrormsg(env));
				return -1;
			}
	    }
	}

	/* column constraint */

	for (v = 0; v < nm; v++) {
	    for (i = 0; i < nm; i++) {
	    	for (j = 0; j < nm; j++) {
	    		ind[j] = calcIndex(i,j,v,nm,nm);
	    		val[j] = 1.0;
	    	}

	    	error = GRBaddconstr(model, nm, ind, val, GRB_EQUAL, 1.0, NULL);
			if (error) {
				printf("ERROR %d 1st GRBaddconstr() - column constraint: %s\n", error, GRBgeterrormsg(env));
				return -1;
			}
	  	}
	}

	/* block constraint */

	for (v = 0; v < nm; v++) {
	    for (block_i = 0; block_i < n; block_i++) {
	    	for (block_j = 0; block_j < m; block_j++) {
	    		count = 0;
	    		for (i = block_i*m; i < (block_i+1)*m; i++) {
	    			for (j = block_j*n; j < (block_j+1)*n; j++) {
	    				ind[count] = calcIndex(i,j,v,nm,nm);
	    				val[count] = 1.0;
	    				count++;
	    			}
	    		}

	        error = GRBaddconstr(model, nm, ind, val, GRB_EQUAL, 1.0, NULL);
				 if (error) {
					 printf("ERROR %d GRBaddconstr() - block constraint: %s\n", error, GRBgeterrormsg(env));
					 return -1;
				 }
	      	}
	    }
	}

	/* Optimize model */
	error = GRBoptimize(model);
	  if (error) {
		  printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
		  return -1;
	  }

	/* Write model to 'sudoku.lp' */
	error = GRBwrite(model, "sudoku.lp");
	  if (error) {
		  printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
		  return -1;
	  }

    /* Get solution information */
    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
	  if (error) {
		  printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
		  return -1;
	  }

    /* solution found */
    if (optimstatus == GRB_OPTIMAL) {
        /* get the solution - the assignment to each variable */
        error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, nm*nm*nm, sol);
    	  if (error) {
    		  printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
    		  return -1;
    	  }
    	for (i = 0; i < nm; i++) {
    	    for (j = 0; j < nm; j++) {
    	    	for (v = 0; v < nm; v++) {
    	    		if (sol[calcIndex(i,j,v,nm,nm)] == 1){
    	    			solutionBoard->board[calcIndex(i,j,0,nm,3)] = v+1;
    	    			printf("%d in index %d,%d which is %d\n", v+1, i,j, calcIndex(i,j,0,nm,3));
    	    		}
    	    	}
    	    }
    	}
    	ret = 1;

    }
    /* no solution found or optimization stopped early*/
    else{
    	ret = 0;
    }

    /* IMPORTANT !!! - Free model and environment */
    free(sol);
    free(ind);
    free(initVals);
    free(val);
    free(vtype);
    GRBfreemodel(model);
    GRBfreeenv(env);

    return ret;
}

