

#include "ActionList.h"
#include "MainAux.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



void freeList(ActionList *list);
void initList(ActionList *list);
int undo(ActionList *list);
int addNewNode(ActionList *list);
int printChanges(GameBoard *before, GameBoard *after, char *func);
int clearTailOfList(ActionList *list);
void copyBoard(GameBoard *oldBoard, GameBoard *newBoard);


int TABLE_SIZE = 4;
int BLOCK_SIZE_N = 2;
int BLOCK_SIZE_M = 2;

int main(){
	ActionList *list = (ActionList*)calloc(1,sizeof(ActionList*));
	initList(list);
	addNewNode(list);
	addNewNode(list);
	list->curr->board->board[2]=2;
	list->curr->board->board[0]=2;
	list->curr->board->board[1]=2;
	undo(list);
	addNewNode(list);
	redo(list);
	undo(list);
	freeList(list);

	return 1;

}



/*real code from here*/

int undo(ActionList *list){
	if(list->curr->prev==0){
		printf("Error: no moves to undo\n");
		return 0;
	}
	printChanges(list->curr->prev->board,list->curr->board,"Undo");
	list->curr = list->curr->prev;

	return 0;
}

int redo(ActionList *list){
	if(list->curr->next==0){
		printf("Error: no moves to redo\n");
		return 0;
	}
	list->curr = list->curr->next;
	printChanges(list->curr->board,list->curr->prev->board,"Redo");
	return 0;
}

int printChanges(GameBoard *before, GameBoard *after, char *func){
	int i,j,val1,val2,index;
	for(i=0;i<BLOCK_SIZE_N;i++){
		for(j=0;j<BLOCK_SIZE_M;j++){
			index=calcIndex(i,j,0,TABLE_SIZE,3);
			val1=(before->board)[index];
			val2=(after->board)[index];
			if(val1!=val2){
				if(val1==0){
					printf("%s %d,%d, from '_' to %d\n",func, i+1,j+1,val2);
				}
				if(val2==0)	{
					printf("%s %d,%d, from %d to '_'\n",func, i+1,j+1,val1);
				}
				if(val1!=0&&val2!=0){
					printf("%s %d,%d, from %d to %d\n",func, i+1,j+1,val1,val2);
				}

			}

		}
	}
	return 0;

}


void copyBoard(GameBoard *oldBoard, GameBoard *newBoard){
	int i,j;
	if(newBoard==0){
		printf("allocation failed. bye!");
		exit(0);
	}
	if(oldBoard==0){
			printf("allocation failed. bye!");
			exit(0);
		}

	for(i=0;i<BLOCK_SIZE_N;i++){
		for(j=0;j<BLOCK_SIZE_M;j++){
				(newBoard->board)[calcIndex(i,j,0,TABLE_SIZE,3)]=(oldBoard->board)[calcIndex(i,j,0,TABLE_SIZE,3)];
				(newBoard->board)[calcIndex(i,j,1,TABLE_SIZE,3)]=(oldBoard->board)[calcIndex(i,j,1,TABLE_SIZE,3)];
				(newBoard->board)[calcIndex(i,j,2,TABLE_SIZE,3)]=(oldBoard->board)[calcIndex(i,j,2,TABLE_SIZE,3)];

			}

	}


}


int addNewNode(ActionList *list){

	Node *newNode = (Node*)calloc(1,sizeof(Node));
	newNode->board = (GameBoard*)calloc(1,sizeof(GameBoard));
	newNode->board->board=(int*)calloc(3*TABLE_SIZE*TABLE_SIZE,sizeof(int));

	copyBoard(list->curr->board, newNode->board);
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

int clearTailOfList(ActionList *list){
	Node *currNode,*next;
	if(list->curr->next==0)
		return 0;
	currNode = list->curr->next;

	while(currNode->next!=0){
		next=currNode->next;
		free(currNode->board->board);
		free(currNode->board);
		free(currNode);
		currNode=next;
	}

	free(currNode->board->board);
	free(currNode->board);
	free(currNode);
	return 0;
}

void reset(ActionList *list){
	list->curr=list->first;
	clearTailOfList(list);
	printf("Board reset\n");
}

/*needs to pre allocate pointer*/
void initList(ActionList* list){
	list->first = (Node*)calloc(1,sizeof(Node));
	list->first->board = (GameBoard*)calloc(1,sizeof(GameBoard));
	list->first->board->board = (int*)calloc(48,sizeof(int));
	/*printf("succesfuly allocated board \n");*/
	list->curr=list->first;
	list->curr->prev=0;
	list->curr->next=0;
	/*printf("finished init \n");*/

}

void freeList(ActionList *list){
	list->curr=list->first;
	clearTailOfList(list);
	free(list->curr->board->board);
	free(list->curr->board);
	free(list->curr);
	free(list);
}





