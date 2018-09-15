/*
 * contains all game structs, global game variables, and all the functions relevant to the game commands.
 * unless stated otherwise, functions return 1 upon finishing successfully.
 * The ActionList is the main struct of the project. the curr node holds the current game board and all actions take place on it.
 * see detailed documentation in header and source file.
 */

#ifndef GAME_H_
#define GAME_H_

/*global game variables*/
extern int BLOCK_SIZE_N;
extern int BLOCK_SIZE_M;
extern int TABLE_SIZE; /* =N*M */
extern int fullCells;
extern char address[256];

int gameMode; /* 0=init, 1=solve, 2=edit */
int markErrors; /*0=no, 1=yes*/

/*
 * Game structs follows.
 * action list structs declared here as well for convenience.
 */

/*
 * the board itself is stored in the "board" field and is a 1d continuous array.
 * converting board coordinates to array coordinate is done by calcIndex method in MainAux module.
 */
typedef struct gameBoardStruct{
	int* board;
} GameBoard;


/*
 * Action list node. contains a board field that points to a gameboard, as well as pointers to prev and next nodes in list.
 */
struct Node {
	GameBoard *board;
	struct Node* next;
	struct Node* prev;
};
typedef struct Node Node;


/*
 * The action list struct. contains pointer to head and current nodes.
 */
struct ActionList{
	Node *curr;
	Node *first;
};
typedef struct ActionList ActionList;



/*
 * set value z to cell (x,y). calls private functions that validates that set is legal.
 */
int setCell(int z, int x, int y, ActionList *list);
/*
 * give hint for cell (x,y), for the board provided as parameter.
 */
void hintCell(GameBoard *board,int x,int y);

/*
 * return if the board is solvable or not using the relevant function. print status is 1 if called by user during game, 0 if called internally.
 */
int validateBoard(GameBoard *board, int printStatus);

/*
 frees resources and exits game
  */
void exitCommand(ActionList *list);
/*
 * prints gameboard. pointer supplied as parameter.
 */
void printBoard(GameBoard *board);

/*
 * checks whether game is over and handles scenario by printing proper messages.
 */
int isGameOver();

/*
 * checks if z is a valid number for cell (x,y).
 */
int isLegalSet(GameBoard *board ,int z, int x, int y);

/*
 * loads board. address supplied in the global field address.
 * cleans the action list (pointer supplied) and places the new board in the first node of the cleaned action list.
 * solveMode is 1 in solve mode, 0 in edit.
 */
int loadBoard(ActionList *list,int solveMode);

/*
 * saves board in the curr node of th list supplied. address supplied in the global field address.
 */
int saveBoard(ActionList *list);

/*
 * checks whether the board is solvable.
 * if printStatus==1, function print relevant messages (for the validate game call).
 * else - function doesn't print, happens when validate is used before save.
 * board pointer supplied as parameter.
 */
int validateBoard(GameBoard *board, int printStatus);

/*fills trivial cells in the board in the curr node of the action list supplied as parameter.*/
int autofill(ActionList *list);

/*
 * prints a message according to the number of possible solutions of the board, according to instructions.
 * board pointer supplied as parameter.
 *
 */
int numSolutions(GameBoard *board);

/*
 * Generates a puzzle by randomly filling X cells with random legal values, solves the resulting board, and then clearing all but Y random cells.
 * board pointer supplied as parameter.
 */
void generateBoard(GameBoard *board, int x, int y);

/*set the markErrors field to 0 or 1 (supplied as val)*/
void setMarkErrors(int val);

/*marks all errors in board. pointer supplied as parameter*/
int markErrorsInBoard(GameBoard *board);

#endif /* GAME_H_ */
