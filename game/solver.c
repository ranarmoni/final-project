#include "game.h"
#include <stdlib.h>
#include <stdio.h>

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
    int temp;
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
	if(getIndex == 1)
		return s->top->index;
	else
		return s->top->value;
}

void setSeed(int seed){
	srand(seed);
}

int countNuberOfSols(GameBoard *originalBoard){
	int* currBoard = (int*)calloc(TABLE_SIZE*TABLE_SIZE*3,sizeof(int));
	int count = 0, i;
	Stack stack = (Stack*)calloc(sizeof(Stack));

    if (!currBoard) {
		printf("Error: calloc has failed\n");
		exit(0);
    }

	memcpy((void*)originalBoard->board,(void*)currBoard);

	initialise(stack);
	do{
		for(i=0;i<TABLE_SIZE;i++){

		}
	}while(stack->top != NULL);
	return count;
}
