/*
 * parser module takes care of parsing the user input and transforming it into arrays that hold all relevant command  information.
 * read command function does initial parsing of the input, identifies the specific command type (or announces that input is invalid) than calls "readSpecificCommand" to finish the command parsing.
 * the output is an array of 4 ints - first entry is the command number (same as in project guide), and following entries hold the rest of the relevant data (not all entries are always full) .
 */
#include <stdio.h>
#include "game.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int BLOCK_SIZE_N;
int BLOCK_SIZE_M;
int TABLE_SIZE;

char address[];
int gameMode;

int * readSpecificCommand(int type, int varAmnt , char *delim);

int checkInt(char*);


/*
 * read command from user and return an int array representation of it.
 * function runs in a loop and reads a line from stdin in each iteration.
 * if the line is properly parsed and the head of the line matches one of the user commands, readSpecificCommand is called to parse the rest of the command.
 */
int * readCommand(){
	char 	*line = (char*)calloc(260,sizeof(char)),
			*token="", *delim = " \t\r\n",dummy[260];
	int i, errState = 0;
	int *command;
	int commands[15][2] = {
		{1,0} ,
		{2,0} ,
		{3,1} ,
		{4,0} ,
		{5,3} ,
		{6,0} ,
		{7,2} ,
		{8,0} ,
		{9,0} ,
		{10,0},
		{11,2},
		{12,0},
		{13,0},
		{14,0},
		{15,0}
	};
	char commandNames[15][15] = {"solve","edit","mark_errors","print_board","set",
			"validate","generate","undo","redo","save","hint","num_solutions","autofill","reset","exit"};
	char c;

	/* check if calloc failed */
	if(line == 0){
		printf("Error: calloc has failed\n");
		exit(0);
	}

	while(!feof(stdin)){
		errState = 0;
		printf("Enter your command:\n");
		/* empty line */
		if(fgets(line, 258, stdin)==NULL)
			break;
		if (sscanf(line,"%s",dummy) <1){ /* stops on spaces as fgets keeps reading them */
			continue;
		}
		if(strlen(line)>256){
			while((c = getc(stdin)) != '\n' && c != EOF);  /* throw away all the left chars over the 256 chars allowed */
			printf("ERROR: invalid command\n");
			continue;
		}

		token = strtok(line, delim);

		/* process the 15 command types and read the right one with the specific command func */
		for(i=0; i<15; ++i){
			if(strcmp(token, commandNames[i]) == 0){
				command = readSpecificCommand(commands[i][0],commands[i][1], delim);
				if (command[0] < 1){
					errState = command[0];
					free(command);
					break;
				}
				free(line);
				return command;
			}
		}
		if(errState == 0)
			printf("ERROR: invalid command\n");
	}
	/* if EOF reached than output exit command */
	command = (int*)calloc(4,sizeof(int));
	command[0] = 15;
	free(line);
	return command;
}

/*
 * PRIVATE METHODS FOLLOW
 */


/*
 * parses a specific command from user input and return an int array representation of it.
 * function recieves function type, amount of variables, and delimiter chars from "readCommand"
 * the function returns an array of 4 ints - first entry is the command number (same as in project guide), and following entries hold the rest of the data.
 */
int * readSpecificCommand(int type, int varAmnt , char *delim){
	int i, isInt;
	int *command = (int*)calloc(4,sizeof(int));
	char *token;

	/* check if calloc failed */
	if(command == 0){
		printf("Error: calloc has failed\n");
		exit(0);
	}
	/* check if fucntion type legal */
	if ((gameMode == 0 && type != 1 && type!=2 && type != 15) ||
			(gameMode == 1 && type == 7) ||
			(gameMode == 2 && (type == 13 || type == 11 || type == 3))){
		command[0] = 0;
		return command;
	}
	command[0] = type;
	if(type==1 || type==2 || type ==10){
		token = strtok(NULL, delim);
		if(token == NULL){
			if (type==2)
				strcpy(address,"");
			else{
				command[0] = 0;
				return command;
			}
		}
		else
			strcpy(address, token);
	}
	/* read x y z */
	for(i=1 ; i<=varAmnt; ++i){
		token = strtok(NULL, delim);
		if(token == NULL){
			command[0] = 0;
			return command;
		}
		/* check if int */
		isInt = checkInt(token);

		command[i] = atoi(token);

		/* check if parameters are legal for the command type  */
		if(type==3 && (!(command[i] == 0 || command[i] == 1) || !isInt) ){
			printf("Error: the value should be 0 or 1\n");
			command[0] = -1;
			return command;
		}
		if(type==5 && ((command[i]>TABLE_SIZE || command[i]<1) || !isInt)){
			if(i!=3 || command[i]<0){
				printf("Error: value not in range 0-%d\n",TABLE_SIZE);
				command[0] = -1;
				return command;
			}
		}
		if(type==11 && ((command[i]>TABLE_SIZE || command[i]<1) || !isInt)){
			printf("Error: value not in range 1-%d\n",TABLE_SIZE);
			command[0] = -1;
			return command;
		}
		if(type==7 && ((command[i]<0 || command[i]>(TABLE_SIZE*TABLE_SIZE-fullCells)) || !isInt)){
				printf("Error: value not in range 0-%d\n",TABLE_SIZE*TABLE_SIZE);
				command[0] = -1;
				return command;
		}
	}
	return command;
}


/*
 * checks if a token consists only of ints (=is an int itself).
 */
int checkInt(char* token){
	int j = 0;
	while(token[j] != '\0'){
		if(!isdigit(token[j])){
			return 0;
		}
		j++;
	}
	return 1;
}

