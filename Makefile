
CC = gcc
CFLAGS = -Wall
SRC = src
OUTPUT = out

$(shell mkdir -p $(OUTPUT))

all:
	$(CC) $(CFLAGS) $(SRC)/main.c -o $(OUTPUT)/main.exe

run: all
	./$(OUTPUT)/main.exe