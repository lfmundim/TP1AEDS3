CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -Werror -std=c99 -pedantic
OBJ = main.o books.o files.o shelves.o sorting.o
DEPS = books.h files.h shelves.h sorting.h
VFLAGS = --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes
EXEC = ./exec

all: exec

exec: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o exec estante* indice livros_ordenados

valgrind:
	valgrind $(VFLAGS) $(EXEC)
run:
	$(EXEC)
