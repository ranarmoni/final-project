CC = gcc
OBJS = ActionList.o MainAux.o game.o main.o parser.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra \
-Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@


main.o: game.h game.c solver.h ActionList.h ActionList.c parser.h main.c 
	$(CC) $(COMP_FLAG) -c $*.c	
	
	
parser.o: game.h parser.c parser.h 
	$(CC) $(COMP_FLAG) -c $*.c	
	
game.o: game.h game.c solver.h parser.h MainAux.h MainAux.c
	$(CC) $(COMP_FLAG) -c $*.c
	
	
ActionList.o: ActionList.h ActionList.c game.o MainAux.o
	$(CC) $(COMP_FLAG) -c $*.c

MainAux.o: MainAux.h MainAux.c game.h 
	$(CC) $(COMP_FLAG) -c $*.c
	

clean:
	rm -f $(OBJS) $(EXEC)
	