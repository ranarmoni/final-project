CC = gcc
OBJS = fileIO.o MainAux.o
EXEC = io
COMP_FLAG = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm

#grb_solver.o: grb_solver.c game.h MainAux.o 
#	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
	
fileIO.o: fileIO.c fileIO.h game.h MainAux.o
	$(CC) $(COMP_FLAG) -c $*.c	

MainAux.o: MainAux.c MainAux.h
	$(CC) $(COMP_FLAG) -c $*.c
	

	
clean:
	rm -f $(OBJS) $(EXEC)
	