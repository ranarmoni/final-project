




//returns GameBoard. main needs to store it in place.

GameBoard* undo(){
	curr = curr->prev;
	printf("Undo: %s",curr->message);

	return curr->board;
}

//returns GameBoard. main needs to store it in place.
GameBoard* redo(){
	curr = curr->next;
	printf("Redo: %s",curr->message);

	return curr->board;
}

int deleteRedo(GameBoard *before, GameBoard *after){


}


int printChanges(GameBoard)

