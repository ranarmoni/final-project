/*
 * parser.c
 *
 *  Created on: 17 May 2018
 *      Author: hp envy
 */
#include <stdio.h>
#include "parser.h"
#include <string.h>
#include <stdlib.h>

int * readSpecificCommand(int type, int varAmnt , char *delim);

/*
 * read the amount of fixed cells 0-80
 */
int readFixedAmnt(){
	int amnt = -1;
	while(amnt<0 || amnt>80 ){
		printf("Please enter the number of cells to fill [0-80]:\n");
		if(scanf("%d", &amnt)==0){
			printf("Error: scanf has failed\n");
			exit(0);
		}
		if(feof(stdin))
			return -1;
		if(amnt<0 || amnt>80)
			printf("Error: Invalid number of cells to fill (should be between 0 and 80)\n");
	}
	return amnt;
}

/*
 * read command from user and return an int array representation of it
 */
int * readCommand(){
	char 	*line = (char*)calloc(1024,sizeof(char)),
			*token, *delim = " \t\r\n";
	int i;
	int *command;
	int commands[5][2] = {
		{1,3} ,
		{2,2} ,
		{3,0} ,
		{4,0} ,
		{5,0}
	};
	char commandNames[5][10] = {"set","hint","validate","restart","exit"};

	/* check if calloc failed */
	if(line == 0){
		printf("Error: calloc has failed\n");
		exit(0);
	}

	while(!feof(stdin)){
		fgets(line,1024,stdin);
		token = strtok(line, delim);

		/* empty line */
		if (token == NULL)
			continue;



		/* process the 5 command types */
		for(i=0; i<5; ++i){
			if(strcmp(token, commandNames[i]) == 0){
				command = readSpecificCommand(commands[i][0],commands[i][1], delim);
				if (command == NULL){
					break;
				}
				free(line);
				return command;
			}
		}
		printf("Error: invalid command\n");
	}
	command = (int*)calloc(4,sizeof(int));
	command[0] = 5;
	free(line);
	return command;
}


int * readSpecificCommand(int type, int varAmnt , char *delim){
	int i;
	int *command = (int*)calloc(4,sizeof(int));
	char *token;

	/* check if calloc failed */
	if(command == 0){
		printf("Error: calloc has failed\n");
		exit(0);
	}

	command[0] = type;
	/* read x y z */
	for(i=1 ; i<=varAmnt; ++i){
		token = strtok(NULL, delim);
		if(token == NULL)
			return NULL;
		command[i] = ((int)strtol(token, NULL, 10))-1;
		if(command[i] == -1){
			return NULL;
		}
	}
	return command;
}


