#Requires mingw bin added to path in windows

CC = gcc
CFLAGS =-Wall

BDIR=bin
SDIR=src
ODIR=obj

BIN=$(BDIR)/program.exe
SRC=$(wildcard $(SDIR)/*.c)
OBJ=$(patsubst $(SDIR)/%.c,$(ODIR)/%.o, $(SRC))

WORDSNAME=words.txt
WORDSFILE=$(BDIR)/$(WORDSNAME)

all: $(BIN) $(WORDSFILE) 

debug: CFLAGS += -g
debug: clean all

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(WORDSFILE): $(WORDSNAME)
	cp $(WORDSNAME) $@

clean:
	rm -f $(BDIR)/* $(ODIR)/*

.PHONY: all clean debug
