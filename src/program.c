#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>

#include "..\include\game.h"

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_WORD_SIZE 100

#define ERROR_MEMORY "Error: Memory allocation failed!" 

int get_word_count(const char* file_name){
    FILE* file = fopen(file_name, "r");
    
    if (file == NULL){
        printf("Unable to open %s\n", file_name);
        fclose(file);
        exit(2);
    }

    int l = 0;
    char c;
    char lastChar;
    while ((c = getc(file)) != EOF){
        if (c == '\n'){
            l++;
        }
        lastChar = c;
    }

    if (lastChar != '\n'){
        l++;
    }

    fclose(file);

    if (l == 0){
        puts("Error: empty words.txt file!");
        fclose(file);
        exit(2);
    }
    return l;
}

int str_find_c(char str[], char c){
    int i, len = strlen(str);
    for (i = 0; str[i] != c; i++){
        if (i > len)
            return 0;
    }
    return i; 
}

void load_words(const char* file_name, char** list, int count){
    FILE* file = fopen(file_name, "r");
    if (file == NULL){
        printf("Unable to open %s\n", file_name);
        fclose(file);

        exit(2);
    }

    char line[MAX_WORD_SIZE];
    for(int i = 0; i < count; i++){
        if (fgets(line, sizeof(line), file) != NULL){
            int len = str_find_c(line, '\n');
            if (len > 0){
                line[len] = '\0';
            }

            strncpy(list[i], line, MAX_WORD_SIZE);
        }
    }

    fclose(file);
}

int main(void){
    srand(time(NULL));
    setlocale(LC_ALL, "");

    #ifdef _WIN32
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;

    GetConsoleMode(handle, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(handle, mode);
    #endif

    const char* words_file = "words.txt";

    int word_count = get_word_count(words_file);
    
    char** word_list = (char**)malloc(word_count * sizeof(char*));

    if (word_list == NULL){
        puts(ERROR_MEMORY);
        exit(-1);
    }

    //Initialize word list
    for(int i = 0; i < word_count; i++){
        word_list[i] = (char*)malloc(MAX_WORD_SIZE * sizeof(char));

        if (word_list[i] == NULL){
            puts(ERROR_MEMORY);
            exit(-1);
        }
    }

    load_words(words_file, word_list, word_count);

    char *word;
    start: //Game loop
    
    word = word_list[rand() % word_count];

    game_start(word);

    puts("\rPlay again? (y, n)");
    char c;
    scanf(" %c", &c);
    switch(c){
        case 'y':
        case 'Y':
            goto start;

        default: break;
    }
    
    //Free memory
    for(int i = 0; i<word_count; i++) free(word_list[i]);
    free(word_list);


    return 0;
}