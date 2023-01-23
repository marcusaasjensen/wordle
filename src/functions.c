#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#endif

#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

#include <stdlib.h>
#include "../functions.h"

char* solution;

char* choose_random_word(const char *filename) {
    FILE *f;
    size_t lineno = 0;
    size_t selected_length;
    char selected[6]; /* Arbitrary, make it whatever size makes sense */
    char current[6];
    selected[0] = '\0'; /* Don't crash if file is empty */
    double random_number = ((double)rand()/(double)RAND_MAX);

    if((f = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Failed to open dictionary. Make sure the dictionary file is inside Wordle's folder.\n");
        exit(1);
    }

    while (fgets(current, sizeof(current), f)) {
        if (random_number < 1.0 / ++lineno) {
            strcpy(selected, current);
        }
    }
    fclose(f);
    selected_length = strlen(selected);
    if (selected_length > 0 && selected[selected_length - 1] == '\n') {
        selected[selected_length - 1] = '\0';
    }
    return strdup(selected);
}

void print_letter_in_color(char letter, int state)
{
    if(state < 0)
    {
        printf("%c", letter);
        return;
    }
#ifdef linux
    if(state == 0)
        printf("%s%c%s", YEL, letter, RESET);
    else
        printf("%s%c%s", GRN, letter, RESET);

#endif
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    if(state == 0)
    {
        SetConsoleTextAttribute(hConsole,
                                FOREGROUND_BLUE);
        printf("%c", letter);
    }
    else
    {
        SetConsoleTextAttribute(hConsole,
                                FOREGROUND_GREEN);
        printf("%c", letter);
    }
    SetConsoleTextAttribute(hConsole,
                            saved_attributes);
#endif
}

void print_word(char word[], int size)
{
    int letter_state;

    char solution_buffer[WORD_MAX_LENGTH] = {};

    strcpy(solution_buffer, solution);

    for(int i = 0 ; i < size ; i++)
    {
        letter_state = -1;
        for(int j = 0 ; j < size ; j++)
        {
            if(word[i] != solution_buffer[j]) continue;

            if (i == j)
            {
                letter_state = 1;
                solution_buffer[j] = '_';
                break;
            }
            else
            if(word[j] != solution_buffer[j])
            {
                letter_state = 0;
                break;
            }
        }
        print_letter_in_color(word[i], letter_state);
    }
}

void print_board(char board[BOARD_MAX_LENGTH][WORD_MAX_LENGTH])
{
    if(board == NULL) return;

    printf("\nBoard:\n\n");
    for(int i = 0 ; i < BOARD_MAX_LENGTH ; i++)
    {
        if(board[i][0] != '*')
            print_word(board[i], WORD_MAX_LENGTH);
        else
            for(int j = 0 ; j < WORD_MAX_LENGTH ; j++, printf("*"));
        printf("\n");
    }
    printf("\n");
}

void format_input(char* dest, char* input, int size)
{
    int ignored = 0;
    int j = 0;
    for(int i = 0 ; *input != '\0' && i < size; input++, i++)
        if(isalpha(*input))
        {
            *dest = (char) toupper(*input);
            dest++;
            j++;
        }
        else
            ignored = 1;

    for( ; j < size; dest++, j++)
        *dest = '\0';

    if(ignored)
        fprintf(stderr, "Characters other than letters are ignored and will only take the 5 next letters from the input.\n");
}

void initialize_board(char board[BOARD_MAX_LENGTH][WORD_MAX_LENGTH])
{
    for(int i = 0 ; i < BOARD_MAX_LENGTH ; i++)
        for(int j = 0 ; j < WORD_MAX_LENGTH ; j++)
            board[i][j] = '*';
}

int compare_word_to_solution(char str[WORD_MAX_LENGTH])
{
    for(int i = 0 ; i < WORD_MAX_LENGTH ; i++)
        if(str[i] != solution[i])
            return 0;
    return 1;
}
