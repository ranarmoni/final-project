#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "solver.h"
#include "MainAux.h"
#include "fileIO.h"

int BLOCK_SIZE_N;
int BLOCK_SIZE_M;
int TABLE_SIZE;

typedef struct node{
    int index;
    int value;
    struct node *next;
} StackNode;

typedef struct {
	StackNode *top;
    int size;
} Stack;

void initialise(Stack *s);
void push(Stack *s, int indx, int val);
void pop(Stack *s);
int getTop(Stack *s, int getIndex);

void initialise(Stack *s){
    s->size = 0;
    s->top = NULL;
}

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

int getTop(Stack *s, int getIndex){
	if(s->top == NULL)
		return -1;
	if(getIndex == 1)
		return s->top->index;
	else
		return s->top->value;
}

void setSeed(int seed){
	srand(seed);
}

int countNumberOfSols(GameBoard *originalBoard){
	GameBoard tempBoard;
	int* currBoard = (int*)calloc(TABLE_SIZE*TABLE_SIZE*3,sizeof(int));
	int count = 0, i, currIndex = 0, currValue;
	Stack s, *stack = &s;

    if (!currBoard) {
		printf("Error: calloc has failed\n");
		exit(0);
    }
    tempBoard.board = currBoard;
	memcpy((void*)currBoard, (void*)originalBoard->board, TABLE_SIZE*TABLE_SIZE*3*sizeof(int));

	initialise(stack);
	do{
		while(1){
			if(currIndex >= calcIndex(TABLE_SIZE-1,TABLE_SIZE-1,2,TABLE_SIZE,3)){ /*solution found if current index is larger than the array */
				count++;
				break;
			}
			else if(currBoard[currIndex] == 0){
				/* push all legal values to stack */
				push(stack, currIndex, 0);
				for(i=1;i<=TABLE_SIZE;i++){
					if(isLegalSet(&tempBoard, i, (currIndex/3)/TABLE_SIZE , (currIndex/3)%TABLE_SIZE)){
						push(stack, currIndex, i);

					}
				}
				break;
			}
			else{
				currIndex += 3;
				continue;
			}
		}
		currIndex = getTop(stack,1);
		currValue = getTop(stack, 0);
		if(currIndex == -1)
			break;
		currBoard[currIndex] = currValue;
		/* if out of options reset board until new move */
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
