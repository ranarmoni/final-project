#include "solver.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int BLOCK_SIZE_N;
int BLOCK_SIZE_M;
int TABLE_SIZE;

typedef struct node{
    int index;
    int value;
    struct node *next;
} Node;

typedef struct {
    Node *top;
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
    Node *np;

    np = (Node *)malloc(sizeof(Node));
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
    Node *np;

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
	/* GameBoard tempBoard; */
	int* currBoard = (int*)calloc(TABLE_SIZE*TABLE_SIZE*3,sizeof(int));
	int count = 0, i, currIndex = 0, currValue;
	Stack s, *stack = &s;

    if (!currBoard) {
		printf("Error: calloc has failed\n");
		exit(0);
    }
/*
    tempBoard.board = currBoard;
*/
	memcpy((void*)originalBoard->board,(void*)currBoard, TABLE_SIZE*TABLE_SIZE*3);

	initialise(stack);
	do{
		if(currIndex > 8){
/*		if(currIndex > calcIndex(TABLE_SIZE,TABLE_SIZE,2,TABLE_SIZE,3)){*/ /*solution found if current index is larger than the array */
			count++;
			printIntArr(currBoard,9);
		}
		else if(currBoard[currIndex] == 0){
			/* push all legal values to stack */
			push(stack, currIndex, 0);
			for(i=1;i<=TABLE_SIZE;i++){
			/*	if(isLegalSet(&tempBoard, (currIndex/3)/TABLE_SIZE , (currIndex/3)%TABLE_SIZE , i)) */
				if(1)
					push(stack, currIndex, i);
			}
		}
		else{
			currIndex += 3;
			continue;
		}
		currIndex = getTop(stack,1);
		currValue = getTop(stack, 0);
		currBoard[currIndex] = currValue;
		/* if out of options reset board until new move */
		while(currValue == 0){
			pop(stack);
			currIndex = getTop(stack,1);
			currValue = getTop(stack, 0);
			currBoard[currIndex] = currValue;
		}
		if(stack->top != NULL)
			pop(stack);
		currIndex += 3;
	}while(stack->top != NULL);
	return count;
}

int main(){
	GameBoard boardel;
	int mat[9] = {0,0,0,0,0,0,0,0,0};
	TABLE_SIZE = 3;
	boardel.board = mat;
	printf("%d solutions\n",countNumberOfSols(&boardel));


	return 1;
}
