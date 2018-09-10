

#include "game.h"


struct Node {
	GameBoard *board;
	struct Node* next;
	struct Node* prev;
};

typedef struct Node Node;

struct ActionList{
	Node *curr;
	Node *first;
};


typedef struct ActionList ActionList;




int undo(ActionList *list);
int redo(ActionList *list);
int addNewNode(ActionList *list);
void reset(ActionList *list);
void initList(ActionList* list);
void copyBoard(GameBoard *oldBoard, GameBoard *newBoard);
void freeList(ActionList *list);

