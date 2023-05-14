CC = gcc
CFLAGS =-Wall -g

BDIR=bin
SDIR=src

SRC=$(wildcard $(SDIR)/*.c)
BIN=$(BDIR)/program.exe

WORDSNAME=words.txt
WORDSFILE=$(BDIR)/$(WORDSNAME)

all: $(BIN) $(WORDSFILE)
$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(WORDSFILE): $(WORDSNAME)
	cp $(WORDSNAME) $@

clean:
	rm -f bin/*

.PHONY: all clean
