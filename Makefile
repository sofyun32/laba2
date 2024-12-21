CC = gcc
CFLAGS = -Wall -Wextra
OBJ = main.o sed_operations.o
EXEC = simplified

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

main.o: main.c operations.h
	$(CC) $(CFLAGS) -c main.c

sed_operations.o: sed_operations.c operations.h
	$(CC) $(CFLAGS) -c sed_operations.c

clean: 
	rm -f $(OBJ) $(EXEC)


