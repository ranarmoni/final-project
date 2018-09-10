

#include "ActionList.h"
#include "MainAux.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>




int initList(ActionList *list);
int undo(ActionList *list);
int addNewNode(ActionList *list);
int printChanges(GameBoard *before, GameBoard *after, char *func);
int clearTailOfList(ActionList *list);

int TABLE_SIZE = 4;
int BLOCK_SIZE_N = 2;
int BLOCK_SIZE_M = 2;

int main(){
	ActionList *list = (ActionList*)calloc(1,sizeof(ActionList));
	initList(list);
	list->curr->board->board = (int*)calloc(48,sizeof(int));
	addNewNode(list);
	(list->curr->board->board)[1]=2;
	undo(list);
	
	return 1;

}



/*real code from here*/

int undo(ActionList *list){
	if(list->curr->prev==0){
		printf("Error: no moves to undo\n");
		return 0;
	}
	list->curr = list->curr->prev;
	printChanges(list->curr->next->board,list->curr->board,"Undo");
	return 0;
}

int redo(ActionList *list){
	if(list->curr->next==0){
		printf("Error: no moves to redo\n");
		return 0;
	}
	list->curr = list->curr->next;
	printChanges(list->curr->prev->board,list->curr->board,"Redo");
	return 0;
}

int printChanges(GameBoard *before, GameBoard *after, char *func){
	int i,j,val1,val2,index;
	for(i=0;i<BLOCK_SIZE_N;i++){
		for(j=0;j<BLOCK_SIZE_M;i++){
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


GameBoard* copyBoard(GameBoard *oldBoard){
	int i,j;
	GameBoard *newBoard=(GameBoard*)calloc(1,sizeof(GameBoard));
	if(newBoard==0){
		printf("allocation failed. bye!");
		exit(0);
	}
	newBoard->board=(int*)calloc(3*BLOCK_SIZE_M*BLOCK_SIZE_N,sizeof(int));
	if(newBoard==0){
			printf("allocation failed. bye!");
			exit(0);
		}
	for(i=0;i<BLOCK_SIZE_N;i++){
			for(j=0;j<BLOCK_SIZE_M;i++){
				(newBoard->board)[0]=(oldBoard->board)[0];
				(newBoard->board)[1]=(oldBoard->board)[1];
				(newBoard->board)[2]=(oldBoard->board)[2];
			}

	}
	return newBoard;
}


int addNewNode(ActionList *list){
	Node *newNode = (Node*)calloc(1,sizeof(Node));
	clearTailOfList(list);
	if(newNode==0){
			printf("allocation failed. bye!");
			exit(0);
		}
	newNode->board = copyBoard(list->curr->board);
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
		free(currNode);
		currNode=next;
	}
	free(currNode);
	return 0;
}

void reset(ActionList *list){
	list->curr=list->first;
	clearTailOfList(list);
	printf("Board reset\n");
}

/*needs to pre allocate pointer*/
int initList(ActionList* list){
	list->first = (Node*)calloc(1,sizeof(Node));
	list->curr=list->first;
	list->curr->prev=0;
	list->curr->next=0;
	list->curr->board=0;
	return 1;
}



