#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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

    int lives, gr_pos;
    bool completed;
    char *guessed_right, *word;

    start: //Game loop
    
    word = word_list[rand() % word_count];

    size_t gr_size = strlen(word) + 1;
    guessed_right = (char*)malloc(sizeof(char) * gr_size);
    
    if (guessed_right == NULL){
        puts(ERROR_MEMORY);
        return -1;
    }

    guessed_right[gr_size-1] = '\0';
    gr_pos = 0;
    lives = 6;

    while (!completed) {
        if (lives == 0){
            printf("Too bad! The word was %s...\n\tGAME OVER\n", word);
            break;
        }

        completed = false;

        if (guessed_right[0] != ' ') guessed_right[0] = ' ';

        printf("Word: ");
        completed = true;
        for (int i=0; i<gr_size-1; i++){
            if (strchr(guessed_right, word[i])){
                putchar(word[i]);
            } else {
                putchar('_');
                completed = false;
            }
        }

        printf("\tLives: %d", lives);

        if (completed){
            printf("\n\nNice!\nYou guessed the word '%s' correctly!\n", word);
            break;
        }

        char guess;
        printf("\nYour guess: ");
        scanf(" %c", &guess);

        if (strchr(word, guess)){
            guessed_right[++gr_pos] = guess;
            continue;
        }

        lives--;
    }

    free(guessed_right);

    puts("Play again? (y, n)");
    char c;
    scanf(" %c", &c);
    switch(c){
        case 'y':
        case 'Y':
            completed = false;
            goto start;
            break;

        default: break;
    }
    
    //Free memory
    for(int i = 0; i<word_count; i++) free(word_list[i]);
    free(word_list);


    return 0;
}