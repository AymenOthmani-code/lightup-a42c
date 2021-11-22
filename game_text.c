#include "game_aux.h"
#include <stdio.h>
#include <stdlib.h>

#define TEXT_INPUT_PROMPT "> ? [h for help]\n"
#define TEXT_ACTION_COMMAND "> action: %s\n"
#define TEXT_HELP "help"
#define TEXT_RESET "reset"
#define TEXT_QUIT "quit"
#define TEXT_ACTION_MOVE "> action: play move '%c' into square (%u,%u)\n"
#define TEXT_ERROR "Error at light bulb (%u,%u)\n"

void reset_game(game g);
void end_game(game g);
void print_errors(cgame g);
void print_invalid_move();
void print_invalid_input();
void print_invalid_command();
void print_help();

int main(void) {
    // Variables
    char c;
    uint i, j;
    int r;
    square squareToAdd;

    // Create game
    game gameBeingPlayed = game_default();

    while (!game_is_over(gameBeingPlayed)) {
        // Intialize variables
        i = 0;
        j = 0;
        squareToAdd = S_BLANK;

        // Print game
        game_print(gameBeingPlayed);

        print_errors(gameBeingPlayed);

        // Read input from user
        printf(TEXT_INPUT_PROMPT);
        r = scanf(" %c", &c);
        if (r == 1) {
            if (c == 'l' || c == 'm' || c == 'b') {
                r = scanf("%u %u", &i, &j);
                if (r == 2) {
                    printf(TEXT_ACTION_MOVE, c, i, j);
                    // Set square to the value of the command
                    switch (c) {
                    case 'l':
                        squareToAdd = S_LIGHTBULB;
                        break;
                    case 'm':
                        squareToAdd = S_MARK;
                        break;
                    case 'b':
                        squareToAdd = S_BLANK;
                        break;
                    }
                    // Check that the square can be added
                    if (game_check_move(gameBeingPlayed, i, j, squareToAdd)) {
                        // Use a mask to remove the state of the square selected
                        // then add the new state squareToAdd = squareToAdd |
                        // (game_get_square(gameBeingPlayed, i, j) & F_MASK);
                        // Play the move
                        game_play_move(gameBeingPlayed, i, j, squareToAdd);
                    } else
                        print_invalid_move();
                } else if (r == EOF) {
                    printf("EOF recieved, ending game\n");
                    break;
                } else
                    print_invalid_input();
            } else if (c == 'h') {
                printf(TEXT_ACTION_COMMAND, TEXT_HELP);
                print_help();
            } else if (c == 'r') {
                printf(TEXT_ACTION_COMMAND, TEXT_RESET);
                reset_game(gameBeingPlayed);
            } else if (c == 'q') {
                printf(TEXT_ACTION_COMMAND, TEXT_QUIT);
                printf("shame\n");
                break;
            } else
                print_invalid_command();
        } else if (r == EOF) {
            printf("EOF recieved, ending game\n");
            break;
        } else
            print_invalid_input();
    }

    if (game_is_over(gameBeingPlayed)) {
        game_print(gameBeingPlayed); // added to validate moodle tests
        printf("congratulation\n");
    }

    end_game(gameBeingPlayed);
    return EXIT_SUCCESS;
}

void reset_game(game g) { game_restart(g); }

void end_game(game g) { game_delete(g); }

void print_errors(cgame g) {
    for (uint i = 0; i < DEFAULT_SIZE; i++)
        for (uint j = 0; j < DEFAULT_SIZE; j++)
            if (game_has_error(g, i, j))
                if (game_is_lightbulb(g, i, j))
                    printf(TEXT_ERROR, i, j);
}

void print_invalid_move() {
    printf("Invalid move\n");
    printf("- i and j need to be between %u and %u respectively\n",
           DEFAULT_SIZE, DEFAULT_SIZE);
    printf("- only non-black squares (not a number or 'w') can be modified\n");
}

void print_invalid_input() {
    printf("Invalid input\n");
    print_help();
}

void print_invalid_command() {
    printf("Invalid command\n");
    print_help();
}

void print_help() {
    printf("- press 'l <i> <j>' to put a light bulb at square (i,j)\n");
    printf("- press 'm <i> <j>' to put a mark at square (i,j)\n");
    printf("- press 'b <i> <j>' to blank square (i,j)\n");
    printf("- press 'r' to restart\n");
    printf("- press 'q' to quit\n");
}
