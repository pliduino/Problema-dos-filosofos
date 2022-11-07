
CC = gcc
CFLAGS = -Wall -pthread
SRC = src
OUTPUT = out
MAIN = main

FILES = $(shell find ./src/*.c)
OBJECTS = $(FILES:.c=.o)


$(shell mkdir -p $(OUTPUT))

%.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

all: $(OBJECTS)
	$(CC) -o $(OUTPUT)/$(MAIN) $(OBJECTS)

run: all
	./$(OUTPUT)/$(MAIN)

clean:
	rm $(OBJECTS) $(OUTPUT)/$(MAIN)