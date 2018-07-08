#include <stdio.h>


typedef struct gameBoardStruct{
	int boardMatrix[9][9][2];
} GameBoard;

GameBoard board;

int isLegalSet(GameBoard *board ,int z, int x, int y);
void printBoard(GameBoard board);

int main(void){

	board.boardMatrix[0][0][0]=1;
	board.boardMatrix[0][1][0]=2;
	board.boardMatrix[0][2][0]=3;
	printBoard(board);
	printf("%d",isLegalSet(&board, 1,0,5));
	return 0;
}




int isLegalSet(GameBoard *board ,int z, int x, int y){
	int i=0;
	int j=0;
	int currRow=x;
	int currCol=y;
	for(;currRow<10;currRow++){ /*scan relevant column for collisions*/
		if(z==board->boardMatrix[currRow][y][0])
			return 0;
	}
	for(;currCol<10;currCol++){/*scan relevant row for collisions*/
			if(z==board->boardMatrix[x][currCol][0])
				return 0;
		}
	currRow=x-(x%3);
	currCol=y-(y%3);
	for(;i<3;i++){/*scan relevant block for collisions, starting top left corner.*/
		for(;j<3;j++){
			if(z==board->boardMatrix[currRow+i][currCol+j][0])
			return 0;
			}
	}
	return 1;

}



/*
 *
int isFixed(int x, int y){
	return board.boardMatrix[x][y][1];
}
*/

/*
 * set value z to cell (x,y)
 */


/*

int setCell(int z, int x, int y){
	if(isFixed(x,y)){
		printf("Error: cell is fixed\n");
		return 0;
	}
	if(!isLegalSet(z,x,y)){
		printf("Error: value is invalid\n");
		return 0;
	}
	board.boardMatrix[x][y][0]=z;
	printBoard(board);
	return 1;
}

*/

 /* checks if z is legal in place (x,y)
 * checks row and col, and then find top left corner of block and scans block
*/
void printBoard(GameBoard board){
	int i, j, k, l, x=0, y=0;

	for(k=0; k<3; k++){
		printf("----------------------------------\n");
		for(l=0; l<3; l++){
		for(i=0; i<3; i++){
				printf("|");
				for(j=0; j<3; j++){
					printf(" ");
					if(board.boardMatrix[x][y][1]==1)
						printf(".");
					else
						printf(" ");
					if(board.boardMatrix[x][y][0]==0)
						printf(" ");
					else
						printf("%d",board.boardMatrix[x][y][0]);
					y++;
				}
				printf(" ");
			}
		printf("|\n");
		y=0;
		x++;
		}
	}
	printf("----------------------------------\n");
}




