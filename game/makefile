CC = gcc
OBJS = parser.o
EXEC = parser

COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
	
parser.o: parser.h parser.c game.h
	$(CC) $(COMP_FLAG) -c $*.c

grb_solver.o: grb_solver.c grb_solver.h
	$(CC) $(COMP_FLAG) -c $*.c

test.o: test.c
	$(CC) $(COMP_FLAG) -c $*.c
	
clean:
	rm -f $(OBJS) $(EXEC)
	