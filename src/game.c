#include "..\include\game.h"

static void read_guess(char* guess){
    printf("\nYour guess: " ERASE_LEND);    
    scanf(" %c", guess);
}

static bool display(char* word, char* guessed_right, int size){
    bool completed = true;
    printf("Word: ");
    for (int i=0; i<size-1; i++){
        if (strchr(guessed_right, word[i])){
            putchar(word[i]);
        } else {
            putchar('_');
            completed = false;
        }
    }
    return completed;
}

void game_start(char* word){
    printf(ERASE_ALL MOVE_HOME);
    
    int lives, gr_pos;
    bool completed = false;
    char *guessed_right, guess;

    size_t gr_size = strlen(word) + 1;

    guessed_right = (char*)malloc(sizeof(char) * gr_size);
    memset(guessed_right, ' ', gr_size);

    if (guessed_right == NULL){
        puts("Failed to allocate memory!");
        free(guessed_right);
        return;
    }

    guessed_right[gr_size-1] = '\0';
    gr_pos = 0;
    lives = 6;

    printf(SAVE_CURSOR);
    while (!completed) {
        printf(LOAD_CURSOR);

        if (lives == 0){
            printf("Too bad! The word was %s...\n" ERASE_LEND "\tGAME OVER\n", word);
            break;
        }

        if (guessed_right[0] != ' '){
            guessed_right[0] = ' ';
        } 

        completed = display(word, guessed_right, gr_size);
        
        printf("\tLives: %d", lives);

        if (completed){
            printf("\n\nNice!\nYou guessed the word '%s' correctly!" MOVE_DOWN(2), word);
            break;
        }

        read_guess(&guess);

        if (strchr(word, guess)){
            if (!strchr(guessed_right, guess)){
                guessed_right[++gr_pos] = guess;
            }
            continue;
        }
        lives--;
    }

    free(guessed_right);
}