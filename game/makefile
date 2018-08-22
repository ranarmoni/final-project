CC = gcc
OBJS = parser.o
EXEC = parser
COMP_FLAG = -ansi -Wall -Wextra \
-Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
	
parser.o: parser.h parser.c game.h
	$(CC) $(COMP_FLAG) -c $*.c

test.o: test.c
	$(CC) $(COMP_FLAG) -c $*.c
	
clean:
	rm -f $(OBJS) $(EXEC)
	