#include "game_aux.h"

#include <stdio.h>
#include <stdlib.h>

#include "game_ext.h"

#define TOP_ROW_NUM "   0123456\n"
#define T_B_ROW_LINE "   -------\n"
#define MAIN_ROW_START "%u |"
#define MAIN_ROW_END "|\n"
#define SQUARE_BLANK " "
#define SQUARE_LIGHT_BULB "*"
#define SQUARE_BLACK_WALL_UNNUMBERED "w"
#define SQUARE_BLACK_WALL_ZERO "0"
#define SQUARE_BLACK_WALL_ONE "1"
#define SQUARE_BLACK_WALL_TWO "2"
#define SQUARE_BLACK_WALL_THREE "3"
#define SQUARE_BLACK_WALL_FOUR "4"
#define SQUARE_MARK "-"
#define SQUARE_LIGHTED "."

#define ERROR_MESSAGE_GENERIC "\nError on printing game: "
#define ERROR_INVALID_CELL_STATE "Invalid cell state at (%u, %u), state = %d.\n"

/* ********** ASSERT ********** */

#define ASSERT(expr)                                                      \
    do {                                                                  \
        if ((expr) == 0) {                                                \
            fprintf(stderr, "[%s:%d] Assertion '%s' failed!\n", __FILE__, \
                    __LINE__, #expr);                                     \
            abort();                                                      \
        }                                                                 \
    } while (0)

/* ************************************************************************** */

void game_print(cgame g) {
    // Validate parameters
    ASSERT(g);

    // Initialise variables
    square cell = S_BLANK;
    square cellState = S_BLANK;
    square cellFlag = S_BLANK;

    // Print numbers at top of game and line
    printf(TOP_ROW_NUM);
    printf(T_B_ROW_LINE);

    // Get width and height of game (use default for now)
    int gameWidth = game_nb_cols(g);
    int gameHeight = game_nb_rows(g);

    // Iterate over rows
    for (uint i = 0; i < gameHeight; i++) {
        // Print row start
        printf(MAIN_ROW_START, i);

        // Iterate over columns
        for (uint j = 0; j < gameWidth; j++) {
            // Get the cell and apply state mask
            cell = game_get_square(g, i, j);
            cellState = cell & S_MASK;
            cellFlag = cell & F_MASK;

            // Print value depending on state of cell
            switch (cellState) {
                case S_BLANK:
                    if (cellFlag == F_LIGHTED)
                        printf(SQUARE_LIGHTED);
                    else
                        printf(SQUARE_BLANK);
                    break;
                case S_LIGHTBULB:
                    printf(SQUARE_LIGHT_BULB);
                    break;
                case S_MARK:
                    printf(SQUARE_MARK);
                    break;
                case S_BLACK0:
                    printf(SQUARE_BLACK_WALL_ZERO);
                    break;
                case S_BLACK1:
                    printf(SQUARE_BLACK_WALL_ONE);
                    break;
                case S_BLACK2:
                    printf(SQUARE_BLACK_WALL_TWO);
                    break;
                case S_BLACK3:
                    printf(SQUARE_BLACK_WALL_THREE);
                    break;
                case S_BLACK4:
                    printf(SQUARE_BLACK_WALL_FOUR);
                    break;
                case S_BLACKU:
                    printf(SQUARE_BLACK_WALL_UNNUMBERED);
                    break;
                default:
                    // In case the state in invalid print an error message and
                    // exit
                    printf(ERROR_MESSAGE_GENERIC);
                    printf(ERROR_INVALID_CELL_STATE, i, j, cell);
                    return;
            }
        }

        // Print row end
        printf(MAIN_ROW_END);
    }

    // Print line at bottom of game
    printf(T_B_ROW_LINE);
}

game game_default(void) {
    // Initialise variables
    square blackWallUnnumbered = S_BLACKU;
    square blackWallOne = S_BLACK1;
    square blackWallTwo = S_BLACK2;

    // Create new empty game
    game newGame = game_new_empty();

    // Set square values
    game_set_square(newGame, 0, 2, blackWallOne);
    game_set_square(newGame, 1, 2, blackWallTwo);
    game_set_square(newGame, 2, 5, blackWallUnnumbered);
    game_set_square(newGame, 2, 6, blackWallTwo);
    game_set_square(newGame, 4, 0, blackWallOne);
    game_set_square(newGame, 4, 1, blackWallUnnumbered);
    game_set_square(newGame, 5, 4, blackWallTwo);
    game_set_square(newGame, 6, 4, blackWallUnnumbered);

    return newGame;
}

game game_default_solution(void) {
    // Initialise variables
    square lightbulb = S_LIGHTBULB;

    // Get default game to get a game prefilled with walls
    game newGameSolution = game_default();

    // Set lightbulbs by playing the moves to update the flags
    game_play_move(newGameSolution, 0, 0, lightbulb);
    game_play_move(newGameSolution, 0, 3, lightbulb);
    game_play_move(newGameSolution, 1, 1, lightbulb);
    game_play_move(newGameSolution, 1, 6, lightbulb);
    game_play_move(newGameSolution, 2, 2, lightbulb);
    game_play_move(newGameSolution, 3, 6, lightbulb);
    game_play_move(newGameSolution, 4, 4, lightbulb);
    game_play_move(newGameSolution, 5, 0, lightbulb);
    game_play_move(newGameSolution, 5, 5, lightbulb);
    game_play_move(newGameSolution, 6, 1, lightbulb);

    return newGameSolution;
}
