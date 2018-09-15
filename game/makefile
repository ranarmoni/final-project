CC = gcc
OBJS = solver.o MainAux.o fileIO.o game.o ActionList.o grb_solver.o main.o parser.o
COMP_FLAG = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56
EXEC = sudoku-console

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm

all: sudoku-console
	

grb_solver.o: grb_solver.c game.h MainAux.o 
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c

main.o: game.h game.c solver.h ActionList.h ActionList.c parser.h main.c 
	$(CC) $(COMP_FLAG) -c $*.c	
	
parser.o: game.h parser.c parser.h 
	$(CC) $(COMP_FLAG) -c $*.c	
	
solver.o: solver.h solver.c game.h game.c MainAux.o fileIO.o game.o
	$(CC) $(COMP_FLAG) -c $*.c	

MainAux.o: MainAux.c MainAux.h game.h
	$(CC) $(COMP_FLAG) -c $*.c
	
fileIO.o: fileIO.c fileIO.h game.h MainAux.o 
	$(CC) $(COMP_FLAG) -c $*.c	
	
game.o: game.h game.c MainAux.o ActionList.o  grb_solver.o fileIO.o
	$(CC) $(COMP_FLAG) -c $*.c	
	
ActionList.o: ActionList.c ActionList.h game.h MainAux.h
	$(CC) $(COMP_FLAG) -c $*.c	


	
clean:
	rm -f $(OBJS) $(EXEC)
	