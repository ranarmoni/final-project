CC = gcc
OBJS = solver.o MainAux.o fileIO.o game.o
EXEC = back
COMP_FLAG = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm

#grb_solver.o: grb_solver.c game.h MainAux.o 
#	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
	
solver.o: solver.h solver.c game.h game.c MainAux.o fileIO.o game.o
	$(CC) $(COMP_FLAG) -c $*.c	

MainAux.o: MainAux.c MainAux.h game.h
	$(CC) $(COMP_FLAG) -c $*.c
	
fileIO.o: fileIO.h game.h MainAux.o 
	$(CC) $(COMP_FLAG) -c $*.c	
	
game.o: game.h game.c MainAux.o
	$(CC) $(COMP_FLAG) -c $*.c	

	
clean:
	rm -f $(OBJS) $(EXEC)
	