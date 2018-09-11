



#ifndef ACTIONLIST_H_
#define ACTIONLIST_H_

#include "game.h"







int undo(ActionList *list);
int redo(ActionList *list);
int addNewNode(ActionList *list);
void reset(ActionList *list);
void initList(ActionList* list);
void copyBoard(GameBoard *oldBoard, GameBoard *newBoard);
void freeList(ActionList *list);
void cleanList(ActionList *list);



#endif
