CC = gcc
OBJS = game.o solver.o parser.o main.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra \
-Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
	
main.o: game.c game.h solver.h solver.c parser.c parser.h main.c
	$(CC) $(COMP_FLAG) -c $*.c
	
solver.o: game.c game.h solver.h solver.c parser.c parser.h
	$(CC) $(COMP_FLAG) -c $*.c
	
parser.o: game.c game.h solver.h solver.c parser.c parser.h
	$(CC) $(COMP_FLAG) -c $*.c
	
game.o: game.c game.h solver.h solver.c parser.c parser.h
	$(CC) $(COMP_FLAG) -c $*.c

	
clean:
	rm -f $(OBJS) $(EXEC)
	