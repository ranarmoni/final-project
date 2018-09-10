CC = gcc
OBJS = ActionList.o MainAux.o
EXEC = ActionList
COMP_FLAG = -ansi -Wall -Wextra \
-Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
	
<<<<<<< HEAD
ActionList.o: ActionList.h ActionList.c game.h MainAux.h
	$(CC) $(COMP_FLAG) -c $*.c

MainAux.o: MainAux.h MainAux.c game.h 
	$(CC) $(COMP_FLAG) -c $*.c

=======
fileIO.o: fileIO.c fileIO.h game.h MainAux.o
	$(CC) $(COMP_FLAG) -c $*.c	

MainAux.o: MainAux.c MainAux.h
	$(CC) $(COMP_FLAG) -c $*.c
	

	
>>>>>>> 629f60eb54750b59cbd89e703fd91859cb390e2a
clean:
	rm -f $(OBJS) $(EXEC)
	