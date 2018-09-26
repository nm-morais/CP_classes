CC=gcc
CFLAGS=-Wall -g -ansi -pedantic -c
LDFLAGS=-lpcre -lpthread


OUTPUT=glife
SRC=config.c game.c main.c mem.c
OBJ=$(patsubst %.c,%.o,$(SRC))

$(OUTPUT): $(OBJ)
	$(CC) -o $(OUTPUT) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(OUTPUT) $(OBJ)
