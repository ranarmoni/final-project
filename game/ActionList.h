/*
 * this module holds the actionList relevant functions. all functions receive a pointer to the action list,
 * and returns 1 upon finishing successfully, unless states otherwise.
 * Implementation details documented in source code.
 */




#ifndef ACTIONLIST_H_
#define ACTIONLIST_H_

#include "game.h"



/*
 * undo last action.
 */
int undo(ActionList *list);
/*
 * undo last action.
 */
int redo(ActionList *list);
/*
 * adds new list node, points to it as curr and cleans tail of list.
 */
int addNewNode(ActionList *list);
/*
 * Undo all moves, reverting the board to its original loaded state. cleans tail of list afterwards.
 */
void reset(ActionList *list);

/*
 * inits a new list (pointer needs to be allocated and provided to function)
 */
void initList(ActionList* list);
/*
 * frees list. used by the exit command
 */
void freeList(ActionList *list);
/*
 * cleans list before loading a board.
 */
void cleanList(ActionList *list);


#endif
