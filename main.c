#include "functions.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    printf("Welcome to WORDLE!\n");
    printf("Made in C by Marcus Aas Jensen.\n\n");

    show_instructions();

    char board[BOARD_MAX_LENGTH][WORD_MAX_LENGTH] = {{}};
    char current_word[WORD_MAX_LENGTH + 1] = {};
    char input[WORD_MAX_LENGTH + 1];

    int current_board_index;

    int is_restarting = 1;

    while(strcmp(current_word, "Q") != 0)
    {
        if(is_restarting)
        {
            solution = choose_random_word(FILE_NAME);
            format_input(solution, solution, WORD_MAX_LENGTH);
            initialize_board(board);
            current_board_index = 0;
            print_board(board);
        }

        is_restarting = 0;

        printf("Enter a 5 letter word (q to quit any time):\n");
        scanf("%s", input);

        format_input(current_word, input, WORD_MAX_LENGTH);

        if(strcmp(current_word, "P") == 0)
        {
            printf("Points: %d\n", points);
            continue;
        }

        if(strcmp(current_word, "I") == 0)
        {
            show_instructions();
            continue;
        }

        if(strcmp(current_word, "Q") == 0) break;

        int is_expected_word = strlen(current_word) == WORD_MAX_LENGTH;

        if(!is_expected_word)
        {
            fprintf(stderr, "The inputted word must be a 5 letter word.\n");
            continue;
        }

        if(!is_word_in_dictionary(current_word, FILE_NAME))
        {
            fprintf(stderr, "The input is not a word in the 5-letters dictionary.\n");
            continue;
        }

        for(int i = 0 ; current_word[i] != '\0' ; i++) board[current_board_index][i] = current_word[i];

        print_board(board);

        int is_word_same_as_solution = compare_word_to_solution(board[current_board_index]);
        if(is_word_same_as_solution)
        {
            printf("Well done! +1 point\n");
            points++;
        }
        else if(current_board_index == 5)
            printf("You have lost!\n");

        if(current_board_index == 5 || is_word_same_as_solution)
        {
            printf("The word was \"%s\".\nPoints: %d\n", solution, points);
            do {
                printf("Restart the game ? (y or n):");
                scanf("%s", input);
                format_input(input, input, 1);
            }
            while(strcmp(input, "Y") != 0 && strcmp(input, "N") != 0 && strcmp(input, "Q") != 0);

            if(strcmp(input, "Y") == 0)
            {
                is_restarting = 1;
                continue;
            }
            else
                break;
        }

        current_board_index++;
    }

    printf("Thanks for playing!");

    return 0;
}

