/*
 * this module contains the exaustive backtracking solver and its relevent structs
 */

#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "solver.h"
#include "MainAux.h"
#include "fileIO.h"

/*
 * local reference to global vars
 */
int BLOCK_SIZE_N;
int BLOCK_SIZE_M;
int TABLE_SIZE;

/*
 * Stack and StackNode are structs implementing the stack for the backtracking algorithm
 * nodes represents a possible assignment for a cell
 * each node holds an index (=<x,y>) in the board ,a possible value and a pointer to the next node in the stack
 *
 * the stack holds a pointer to the top of the stack and info about its size in nodes.
 */
typedef struct node{
    int index;
    int value;
    struct node *next;
} StackNode;

typedef struct {
	StackNode *top;
    int size;
} Stack;

/*
 * function declarations. see documentation in the code.
 */
void initialise(Stack *s);
void push(Stack *s, int indx, int val);
void pop(Stack *s);
int getTop(Stack *s, int getIndex);

/*
 * Initialize a new empty stack, receives a pointer to a new uninitialized stack
 */
void initialise(Stack *s){
    s->size = 0;
    s->top = NULL;
}

/*
 * push a new node to stack given the nodes values
 * node index = indx and value = val
 */
void push(Stack *s, int indx, int val){
	StackNode *np;

    np = (StackNode *)malloc(sizeof(StackNode));
    if (np == NULL) {
		printf("Error: calloc has failed\n");
		exit(0);
    }

    np->index = indx;
    np->value = val;
    np->next = s->top;
    s->top = np;

    s->size++;
}

/*
 * pops the last node of the stack
 */
void pop(Stack *s){
	StackNode *np;

    if (s->top == NULL) {
        printf("stack is empty");
    }

    np = s->top;
    s->top = np->next;
    s->size--;
    free(np);
}

/*
 * queries the top node in the stack for its index and value according to getIndex parameter
 * getIndex == 1 --> function returns the index in the top node
 * getIndex == 0 --> function returns the value in the top node
 */
int getTop(Stack *s, int getIndex){
	if(s->top == NULL)
		return -1;
	if(getIndex == 1)
		return s->top->index;
	else
		return s->top->value;
}

/*
 * returns the number of possible solutions for a given sudoku board using the above implemented stack
 * the algorithm traveses the board from start to finish.
 * for each empty cell we insert 0 as a possible value for the cell
 * and then insert all non-zero possible values to the stack together with the relevant index.
 * after doing so we take out the top value, set it to the cell and progress to the next cell.
 * if we reached the end of the board it means we found a solution and we increase the counter.
 * when all the values are exhausted (or none found) 0 is set to the cell since that was the first value pushed
 * and we backtrack to the previous cell.
 */
int countNumberOfSols(GameBoard *originalBoard){
	GameBoard tempBoard;
	int* currBoard = (int*)calloc(TABLE_SIZE*TABLE_SIZE*3,sizeof(int));
	int count = 0, i, currIndex = 0, currValue;
	Stack s, *stack = &s;

    if (!currBoard) {
		printf("Error: calloc has failed\n");
		exit(0);
    }
    /* copy original board so no changes are mades to it */
    tempBoard.board = currBoard;
	memcpy((void*)currBoard, (void*)originalBoard->board, TABLE_SIZE*TABLE_SIZE*3*sizeof(int));

	initialise(stack);
	do{
		/* progress the index of the backtracker and fill stack */
		while(1){
			/*solution found if current index is larger than the array size */
			if(currIndex >= calcIndex(TABLE_SIZE-1,TABLE_SIZE-1,2,TABLE_SIZE,3)){
				count++;
				break;
			}
			else if(currBoard[currIndex] == 0){
				/* push all legal values to stack, 0 first*/
				push(stack, currIndex, 0);
				for(i=1;i<=TABLE_SIZE;i++){
					if(isLegalSet(&tempBoard, i, (currIndex/3)/TABLE_SIZE , (currIndex/3)%TABLE_SIZE)){
						push(stack, currIndex, i);

					}
				}
				break;
			}
			/* skip full cells */
			else{
				currIndex += 3;
				continue;
			}
		}
		/* after stack was filled with new values for a cell we use the top node for assignment and pop it*/
		currIndex = getTop(stack,1);
		currValue = getTop(stack, 0);
		/* check for empty stack */
		if(currIndex == -1)
			break;
		currBoard[currIndex] = currValue;
		/* when backtracking (popping and assigning 0 value) we might need to backtrack several cells */
		while(currValue == 0){
			pop(stack);
			currIndex = getTop(stack,1);
			currValue = getTop(stack, 0);
			if(currIndex == -1)
				break;
			currBoard[currIndex] = currValue;
		}
		if(stack->top != NULL)
			pop(stack);
		currIndex += 3;
	} while(stack->top != NULL);
	free(currBoard);
	return count;
}
