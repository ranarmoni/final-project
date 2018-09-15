/*
 * this module contains the IO functions that deal with files - load and save.
 * for both functions - filename and board pointers are provided as parameters.
 * both functions are "wrapped" by a game function that takes care of all other necessary behaviors like printing messages etc.
 */

#ifndef FILEIO_H_
#define FILEIO_H_


/*
 * loads board from file to a game board.
 * file path, board pointer and game mode provided as parameters.
 * if the file is loaded in solve mode, setFixed is provided as 1 and all cells marked as fixed.
 * if the file is loaded in edit mode, setFixed is provided as 0 and cells aren't marked as fixed.
 */
int loadFile(char *filename, GameBoard *newBoard, int setFixed);

/*
 * saves board to file.
 * file path, board pointer provided as parameters.
 * save format is according to project instructions.
 */
int saveFile(char *filename, GameBoard *newBoard);


#endif /* FILEIO_H_ */
