#pragma once

#define FILE_NAME "./dictionary"
#define WORD_MAX_LENGTH 5
#define BOARD_MAX_LENGTH 6
#define DICTIONARY_LENGTH 5757
#ifdef linux
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"
#endif

extern char* solution;
static int points = 0;

void show_instructions();
int is_word_in_dictionary(char word[], const char *filename);
int rand_range(int lower, int upper);
char* choose_random_word(const char *filename);
void print_letter_in_color(char letter, int state);
int nb_occurrence(char word[], char letter);
void print_word(char word[], int size);
void print_board(char board[BOARD_MAX_LENGTH][WORD_MAX_LENGTH]);
void format_input(char *dest, char *input, int size);
void initialize_board(char board[BOARD_MAX_LENGTH][WORD_MAX_LENGTH]);
int compare_word_to_solution(char str[WORD_MAX_LENGTH]);