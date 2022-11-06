
CC = gcc
CFLAGS = -Wall
SRC = src
OUTPUT = out


all:
	gcc $(CFLAGS) $(SRC)/main.c -o $(OUTPUT)/main.exe

run:
	./src/main.exe