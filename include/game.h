#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Ansi codes
#define SAVE_CURSOR  "\e7"
#define LOAD_CURSOR  "\e8"
#define ERASE_LEND   "\e[0K"
#define ERASE_ALL    "\e[2J"
#define MOVE_HOME    "\e[H"
#define MOVE_DOWN(l) "\e["#l"B"


void game_start(char *word);