


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
	int i,j,val1,val2;
	for(i=0;i<BLOCK_SIZE_N;i++){
		for(j=0;j<BLOCK_SIZE_M;i++){
			val1=(before->board)[i][j][0];
			val1=(after->board)[i][j][0];
			if(val1!=val2){
				if(val1==0){
					printf("%s %f,%f, from '_' to %f\n",func, i+1,j+1,val2);
				}
				if(val2==0)	{
					printf("%s %f,%f, from %f to '_'\n",func, i+1,j+1,val1);
				}
				if(val1!=0&&val2!=0){
					printf("%s %f,%f, from %f to %f\n",func, i+1,j+1,val1,val2);
				}
			}
		}
	}
	return 0;

}


GameBoard* copyBoard(GameBoard *oldBoard){
	int i,j;
	newBoard=(GameBoard*)calloc(1,sizeof(GameBoard));
	if(NewBoard==0){
		printf("allocation failed. bye!");
		exit();
	}
	newBoard->board=(int*)calloc(3*BLOCK_SIZE_M*BLOCK_SIZE_N,sizeof(int));
	if(NewBoard==0){
			printf("allocation failed. bye!");
			exit();
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


void addNewNode(ActionList *list){
	clearTailOfList(list);
	Node *newNode = (Node*)calloc(1,sizeof(Node));
	if(NewNode==0){
			printf("allocation failed. bye!");
			exit();
		}
	newNode->board = copyBoard(list->curr->board);
	newNode->prev = list->curr;
	newNode->next==0;
	list->curr->next = newNode;
	list->curr=newNode;
	return 0;
}

int clearTailOfList(ActionList *list){
	Node curr,next;
	if(list->curr->next==0)
		return 0;
	curr = list->curr->next;
	while(curr->next!=0){
		next=curr->next;
		free(curr);
		curr=next;
	}
	free(curr);
	return 0;
}

void reset(ActionList *list){
	list->curr=list->head;
	clearTailOfList(list);
	printf("Board reset\n");
}


ActionList* initList(){
	ActionList *list = (ActionList*)calloc(1,sizeof(ActionList));
	list->first = (Node*)calloc(1,sizeof(Node));
	list->curr=list->first;
	list->curr->prev=0;
	list->curr->next=0;
	list->curr->board=0;
	return list;
}

void main(){
	ActionList list = initList();
	list->board =
}


