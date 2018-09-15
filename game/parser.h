/*
 * parser module takes care of parsing the user input and transforming it into arrays that hold all relevant command  information.
 * read command function does initial parsing of the input, identifies the specific command type (or announces that input is invalid) than calls "readSpecificCommand" to finish the command parsing.
 * the output is an array of 4 ints - first entry is the command number (same as in project guide), and following entries hold the rest of the relevant data (not all entries are always full) .
 */

#ifndef PARSER_H_
#define PARSER_H_

/*
 * read command from user and return an int array representation of it.
 * the function returns an array of 4 ints - first entry is the command number (same as in project guide), and following entries hold the rest of the data.
 */
int * readCommand();





#endif /* PARSER_H_ */
