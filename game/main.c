#include "game.h"
#include "solver.h"
#include "parser.h"
#include <stdio.h>

#define true 1

int main(){
	int *command;
	if(startGame() == 0){
		exitCommand();
		return 1;
	}
	while(1){
		command = readCommand();
		if(command[0]==1 && !isGameOver()){ /* command is "set" */
			setCell(command[3], command[1], command[2]);
			continue;
		}
		if(command[0]==2 && !isGameOver()){ /* command is "hint" */
			hintCell(command[1],command[2]);
			continue;
		}
		if(command[0]==3 && !isGameOver()){ /*command is "validate"*/
			validateBoard();
			continue;
		}
		if(command[0]==4){/* command is "restart"*/
			restartGame();
			continue;
		}
		if(command[0]==5){ /*command is "exit" */
			exitCommand();
			free(command);
			return 1;
		}
		else{ /* invalid command or set/hint/validate after puzzle solved */
			printf("Error: invalid command\n");

		}

	}

	return 1;
}
