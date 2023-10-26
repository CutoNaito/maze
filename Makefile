CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Werror

TARGET = bin/maze

SRC = $(wildcard src/*.c)

$(TARGET): $(SRC)
	$(CC) $^ -o $@ $(CFLAGS)
