CC = gcc
OBJS = ActionList.o MainAux.o
EXEC = ActionList
COMP_FLAG = -ansi -Wall -Wextra \
-Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
	
ActionList.o: ActionList.h ActionList.c game.h MainAux.h
	$(CC) $(COMP_FLAG) -c $*.c

MainAux.o: MainAux.h MainAux.c game.h 
	$(CC) $(COMP_FLAG) -c $*.c

clean:
	rm -f $(OBJS) $(EXEC)
	