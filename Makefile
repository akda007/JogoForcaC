CC = gcc
CFLAGS =-Wall -g

BDIR=bin
SDIR=src
ODIR=obj

BIN=$(BDIR)/program.exe

SRC=$(wildcard $(SDIR)/*.c)
OBJ=$(patsubst $(SDIR)/%.c,$(ODIR)/%.o, $(SRC))


WORDSNAME=words.txt
WORDSFILE=$(BDIR)/$(WORDSNAME)

all: $(BIN) $(WORDSFILE)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(WORDSFILE): $(WORDSNAME)
	$(COPY) $(WORDSNAME) $@

clean:
	rm -f $(BDIR)/* $(ODIR)/*

.PHONY: all clean
