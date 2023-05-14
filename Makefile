CC = gcc
CFLAGS =-Wall -g

BDIR=bin
SDIR=src

SRC=$(wildcard $(SDIR)/*.c)
BIN=$(BDIR)/program.exe

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f bin/*

.PHONY: all clean
