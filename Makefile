#Requires mingw bin added to path in windows

CC = gcc
CFLAGS =-Wall -I$(IDIR)

BDIR=bin
SDIR=src
ODIR=obj
IDIR=includes

BIN=$(BDIR)/game.exe
SRC=$(wildcard $(SDIR)/*.c)
OBJ=$(patsubst $(SDIR)/%.c,$(ODIR)/%.o, $(SRC))
INC=$(wildcard $(IDIR)/*.h)

WORDSNAME=words.txt
WORDSFILE=$(BDIR)/$(WORDSNAME)

all: $(BIN) $(WORDSFILE) 

debug: CFLAGS += -g
debug: clean all

$(BIN): $(OBJ) $(INC) | $(BDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ): $(ODIR)/%.o: $(SDIR)/%.c $(INC) | $(ODIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(ODIR):
	mkdir -p $@

$(BDIR):
	mkdir -p $@

$(WORDSFILE): $(WORDSNAME)
	cp $(WORDSNAME) $@

clean:
	rm -f $(BDIR)/* $(ODIR)/*

.PHONY: all clean debug
