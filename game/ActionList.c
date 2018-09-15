/*
 * this module holds the actionList relevant functions. all functions receive a pointer to the action list,
 * and returns 1 upon finishing successfully, unless states otherwise.
 */



#include "ActionList.h"
#include "MainAux.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



void freeList(ActionList *list);
void cleanList(ActionList *list);
void initList(ActionList *list);
int undo(ActionList *list);
int addNewNode(ActionList *list);
int trackChanges(GameBoard *before, GameBoard *after, char *func, int print);
int clearTailOfList(ActionList *list);
void copyBoard(GameBoard *oldBoard, GameBoard *newBoard);


int TABLE_SIZE;
int BLOCK_SIZE_N;
int BLOCK_SIZE_M;
int fullCells;


/*
 * undo last action. performed by moving the curr pointer back and printing the diffrences using "printChanges"
 */

int undo(ActionList *list){
	if(list->curr->prev==0){
		printf("Error: no moves to undo\n");
		return 0;
	}
	list->curr=list->curr->prev;
	printBoard(list->curr->board);
	trackChanges(list->curr->board,list->curr->next->board,"Undo", 1);

	return 0;
}

/*
 * redo last action. performed by moving the curr pointer forward and printing the diffrences using "printChanges"
 */

int redo(ActionList *list){
	if(list->curr->next==0){
		printf("Error: no moves to redo\n");
		return 0;
	}
	list->curr = list->curr->next;
	printBoard(list->curr->board);
	trackChanges(list->curr->board,list->curr->prev->board,"Redo",1);
	return 0;
}

/*
 * prints changes between 2 boards - before and after a redo/undo call. used by redo and undo.
 * receives the 2 board pointers and name of function (undo/redo) as parameters.
 */

int trackChanges(GameBoard *before, GameBoard *after, char *func, int print){
	int i,j,val1,val2,index;
	for(i=0;i<TABLE_SIZE;i++){
		for(j=0;j<TABLE_SIZE;j++){
			index=calcIndex(i,j,0,TABLE_SIZE,3);
			val1=(before->board)[index];
			val2=(after->board)[index];

			if(val1!=val2){
				if(val2==0){
					if(print)
						printf("%s %d,%d: from _ to %d\n",func,j+1,i+1,val1);
					fullCells++;
				}
				if(val1==0)	{
					if(print)
						printf("%s %d,%d: from %d to _\n",func,j+1,i+1,val2);
					fullCells--;
				}
				if(val1!=0&&val2!=0){
					if(print)
						printf("%s %d,%d: from %d to %d\n",func,j+1, i+1,val2,val1);
				}

			}



		}
	}
	return 0;

}


/*
 * adds a new node to the list and copies the curr board into it.
 * alters pointers accordingly.
 * cleans tail of actionlist.
 */
int addNewNode(ActionList *list){

	Node *newNode = (Node*)calloc(1,sizeof(Node));
	newNode->board = (GameBoard*)calloc(1,sizeof(GameBoard));
	newNode->board->board=(int*)calloc(3*TABLE_SIZE*TABLE_SIZE,sizeof(int));

	memcpy((void*)newNode->board->board,(void*)list->curr->board->board,TABLE_SIZE*TABLE_SIZE*3*sizeof(int));
	clearTailOfList(list);
	if(!newNode){
			printf("allocation failed. bye!");
			exit(0);
		}
	newNode->prev = list->curr;
	newNode->next=0;
	list->curr->next = newNode;
	list->curr=newNode;

	return 0;
}

/*
 * clears tail of actionlist and frees memory.
 */

int clearTailOfList(ActionList *list){
	Node *currNode,*next;
	if(list->curr->next==NULL)
		return 0;
	currNode = list->curr->next;

	while(currNode->next!=NULL){
		next=currNode->next;
		free(currNode->board->board);
		free(currNode->board);
		free(currNode);
		currNode=next;
	}

	free(currNode->board->board);
	free(currNode->board);
	free(currNode);
	list->curr->next=NULL;
	return 0;
}

/*
 * resets list by changing the curr pointer to the head of the list and cleaning the tail.
 */
void reset(ActionList *list){
	trackChanges(list->first->board,list->curr->board,"reset", 0);
	list->curr=list->first;
	clearTailOfList(list);
	printf("Board reset\n");
}

/*
 * initiates list nodes and fields.
 */
void initList(ActionList* list){
	list->first = (Node*)calloc(1,sizeof(Node));
	list->first->board = (GameBoard*)calloc(1,sizeof(GameBoard));
	list->first->board->board = NULL;
	list->curr=list->first;
	list->curr->prev=NULL;
	list->curr->next=NULL;

}

/*
 *cleans the list and returnes an initiated empty list.
 */
void cleanList(ActionList *list){
	list->curr=list->first;
	clearTailOfList(list);
	free(list->curr->board->board);
	free(list->curr->board);
	list->first->board = (GameBoard*)calloc(1,sizeof(GameBoard));
	list->first->next=NULL;
	list->first->prev=NULL;


	}

/*
 * frees all memory used by list.
 */

void freeList(ActionList *list){
	cleanList(list);
	free(list->curr->board);
	free(list->curr);
	free(list);
}





