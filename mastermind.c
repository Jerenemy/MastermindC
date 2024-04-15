/* COMP 211 ch1: mastermind
 *
 * J. Zay
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

const int CODE_LEN = 4 ;
const int COLOR_N = 6;
const int MAX_GUESSES = 4 ;

enum color {GREEN, BLUE, RED, YELLOW, WHITE, ORANGE} ;    

/* generate_random_n(): int = n, where n is a random int in range [0, COLOR_N - 1]
 */
int generate_random_n() {
    return lrand48() % (COLOR_N) ;
}

/* generate_random_code(code: enum color[]): void
 * Post-condition: code is assigned a random 4 enum color values (duplicate colors ARE allowed, empty slots NOT allowed). 
 */
void generate_random_code(enum color code[]) {
    for (int i=0; i<CODE_LEN; i+=1) {
        code[i] = generate_random_n() ;
    }     
}

/* compare_arr_corr_poss(code: enum color[], guess: enum color[]): int = correct, where correct is the 
 * number of items in guess that are equal to and in the same position as items in code.
 */
int compare_arr_corr_poss(enum color code[], enum color guess[]) {
    int correct = 0 ;
    for (int i=0; i<CODE_LEN; i+=1) {
        if (code[i] == guess[i]) {
            correct += 1 ;
        }
    }
    return correct ;
}

/* compare_arr_corr_poss(code: enum color[], guess: enum color[]): int = incorrect, where incorrect is the 
 * number of items in guess that are equal to and NOT in the same position as items in code.
 */
int compare_arr_inc_poss(enum color code[], enum color guess[]) {
    int incorrect = 0 ;
    for(int i=0; i<CODE_LEN; i+=1) {
        for (int j=0; j<CODE_LEN; j+=1){
            if (code[i] != guess[i] && code[j] != guess[j]) {
                if (code[i] == guess[j]) {
                    incorrect += 1 ;
                    break ;
                }
            }
        }
    }
    return incorrect ;
}

/* create_char_arr(color_key: char[]): void
 * Post-condition: color_key is assigned char values, the indices of each are the color constants in enum color, 
 * the values of each are the capitalized first letter of the corresponding color's name at that value's index.
 */
void create_char_arr(char color_key[]) {
    color_key[GREEN] = 'G' ;
    color_key[BLUE] = 'B' ;
    color_key[RED] = 'R' ;
    color_key[YELLOW] = 'Y' ;
    color_key[WHITE] = 'W' ;
    color_key[ORANGE] = 'O' ; 
}

/* convert_enum_to_char_array(code: enum color[], color_key: char[], char_code: char[]): void
 * Post-condition: char_code is assigned with the characters (the first letter of each color)
 * that correspond to the enum color values of code. 
 */
void convert_enum_to_char_array(enum color code[], char color_key[], char char_code[]) {
    for (int i=0; i<CODE_LEN; i+=1) {
        char_code[i] = color_key[code[i]] ;
    }
}

/* convert_char_to_enum_array(guess: enum color[], color_key: char[], char_guess: char[]): void
 * Post-condition: guess is assigned with the enum color values that correspond with the letters in char_guess.
 */
void convert_char_to_enum_array(enum color guess[], char color_key[], char char_guess[]) {
    for (int i=0; i<CODE_LEN; i+=1) {
        for (int j=0; j<COLOR_N; j+=1) {
            if (char_guess[i] == color_key[j]) {
                guess[i] = j ;
                break ;
            }
        }
    }
}

/* play_game(code: enum color[], guess: enum color[], char_code: char[], char_guess: char[], color_key: char[]): int = 1, if the player guesses the code correctly within the set number of guesses
 *                                                                                                                   = 0, if the player fails to guess the code correctly within the set number of guesses
 */
int play_game(enum color code[], enum color guess[], char char_code[], char char_guess[], char color_key[]) {
    generate_random_code(code) ;
    create_char_arr(color_key) ;
    convert_enum_to_char_array(code, color_key, char_code) ;
    printf("The secret code is %s\n", char_code) ;
    for (int i=0; i<MAX_GUESSES; i+=1) {
        printf("Please enter your guess as a string of exactly 4 characters: ") ;
        scanf(" %s", char_guess) ;
        convert_char_to_enum_array(guess, color_key, char_guess) ;
        printf("You got %d correct colors in the right position and %d colors in the wrong position.\n", compare_arr_corr_poss(&code[0], &guess[0]), compare_arr_inc_poss(&code[0], &guess[0]));
        if (compare_arr_corr_poss(code, guess) == 4) {
            printf("Congratulations, you win!\n") ;
            return 1 ;
        }
    } 
    printf("Too bad, you lost. The code was %s\n", char_code) ;
    return 0 ;
}

int main(void) {
    srand48(time(NULL)) ;

    enum color code[CODE_LEN] ;
    enum color guess[CODE_LEN] ;
    char char_code[CODE_LEN + 1] ; 
    char color_key[COLOR_N + 1] ;
    char char_guess[CODE_LEN + 1] ;
    int games_played = 0 ;
    int games_won = 0 ;
    char play_again ; 
    
    printf("Welcome to Mastermind!\nEnter a guess as a string of 4 characters, where they must be\nG - Green\nB - Blue\nR - Red\nY - Yellow\nW - White\nO - Orange.\n");
    do
    {
        if(play_game(code, guess, char_code, char_guess, color_key) == 1) {
            games_won += 1 ;
        }
        games_played += 1 ;
        printf("Would you like to play again (y/n)? ") ;
        scanf(" %c", &play_again) ;
    } while (play_again == 'y') ;
    printf("You won %d/%d games.\n", games_won, games_played) ;
    return 0 ;    
}