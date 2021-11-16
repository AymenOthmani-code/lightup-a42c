#define __USE_GNU
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_test_commun.c"

/* ********** TEST GAME CHECK MOVE ********** */

bool test_game_check_move()
{
    return true;
}

/* ********** TEST GAME PLAY MOVE ********** */

bool test_game_play_move()
{
    return true;
}

/* ********** TEST GAME UPDATE FLAGS ********** */

bool test_game_update_flags()
{
    return true;
}

/* ********** TEST GAME IS OVER ********** */

bool test_game_is_over()
{
    return true;
}

/* ********** TEST GAME RESTART ********** */

bool test_game_restart()
{
    // [1] Test game default and game default solution
    game gameDefault = game_default();
    game gameDefaultSolution = game_default_solution();
    game_restart(gameDefaultSolution);

    // restarting game default solution should give game default
    ASSERT(game_equal(gameDefault, gameDefaultSolution));

    // cean-up test game default and game default solution
    game_delete(gameDefault);
    game_delete(gameDefaultSolution);

    // [2] Test of game restart on each square for each value
    square *allSquares = create_array_all_values();
    game testGame = game_new_empty();

    // test each square
    for (uint height = 0; height < DEFAULT_SIZE; height++)
    {
        for (uint width = 0; width < DEFAULT_SIZE; width++)
        {
            // for each possible value of a square
            for (uint i = 0; i < SIZE_ALL_VALUES; i++)
            {
                // set the square to the value and restart it
                game_set_square(testGame, height, width, allSquares[i]);
                // use state to test as in all situations the flags need to be removed
                square squareState = game_get_state(testGame, height, width);

                game_restart(testGame);
        
                // if it is black then check that it stays black else it should be blank
                if (squareState & S_BLACK)
                    ASSERT(game_get_square(testGame, height, width) == squareState);
                else
                    ASSERT(game_get_square(testGame, height, width) == S_BLANK);
            }

            // reset square to empty
            game_set_square(testGame, height, width, S_BLANK);
        }
    }

    // Clean-up test game restart on each square for each value
    free(allSquares);
    game_delete(testGame);

    return true;
}

/* ********** USAGE ********** */

void usage(int argc, char *argv[])
{
    fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[])
{
    if (argc == 1)
        usage(argc, argv);

    // start test
    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool ok = false;
    if (strcmp("game_check_move", argv[1]) == 0)
        ok = test_game_check_move();
    else if (strcmp("game_play_move", argv[1]) == 0)
        ok = test_game_play_move();
    else if (strcmp("game_update_flags", argv[1]) == 0)
        ok = test_game_update_flags();
    else if (strcmp("game_is_over", argv[1]) == 0)
        ok = test_game_is_over();
    else if (strcmp("game_restart", argv[1]) == 0)
        ok = test_game_restart();
    else
    {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // print test result
    if (ok)
    {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}
