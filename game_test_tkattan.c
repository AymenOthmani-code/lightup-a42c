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
    // [1] Test that out of grid returns false
    game newGame = game_new_empty();
    ASSERT(!game_check_move(newGame, DEFAULT_SIZE + 1, -1, S_BLANK));
    game_delete(newGame);

    // [2] Test that for each square we can play everything that is playable
    game testGame = game_new_empty();
    square *allSquares = create_array_all_values();

    // test each square
    for (uint row = 0; row < DEFAULT_SIZE; row++)
    {
        for (uint column = 0; column < DEFAULT_SIZE; column++)
        {
            // test each possible starting value of a square
            for (uint startingValue = 0; startingValue < SIZE_ALL_VALUES; startingValue++)
            {
                // set the square to the starting value
                game_set_square(testGame, row, column, allSquares[startingValue]);

                // get the current square for tests
                square currentSquare = game_get_square(testGame, row, column);

                // check each possible move on the square
                for (uint testValue = 0; testValue < SIZE_ALL_VALUES; testValue++)
                {
                    // if the square is not black and we are trying to add a blank, lightbulb or a mark check move needs to be true
                    if (!(currentSquare & S_BLACK) && ((allSquares[testValue] == S_BLANK) ||
                                                       (allSquares[testValue] == S_LIGHTBULB) ||
                                                       (allSquares[testValue] == S_MARK)))
                        ASSERT(game_check_move(testGame, row, column, allSquares[testValue]));
                    else
                        ASSERT(!game_check_move(testGame, row, column, allSquares[testValue]));
                }

                // reset the square to blank
                game_set_square(testGame, row, column, S_BLANK);
            }
        }
    }

    // clean up tests
    game_delete(testGame);
    free(allSquares);

    return true;
}

/* ********** TEST GAME PLAY MOVE ********** */

bool test_game_play_move()
{
    // Test if square is set correctly for each possible value for every square
    game testGame = game_new_empty();
    uint size_allPlayableValues = 3;
    square allPlayableValues[3] = {S_BLANK, S_MARK, S_LIGHTBULB};
    uint size_allAjacentSquares = 2;
    square allAjacentSquares[2] = {S_BLANK, S_LIGHTBULB};
    uint size_allModifiableSquares = 7;
    square allModifiableSquares[7] = {
        S_BLANK, S_LIGHTBULB, S_MARK, S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED, S_LIGHTBULB | F_LIGHTED | F_ERROR, S_MARK | F_LIGHTED};

    // test each square
    for (uint row = 0; row < DEFAULT_SIZE; row++)
    {
        for (uint column = 0; column < DEFAULT_SIZE; column++)
        {
            // calculate value of ajacent row and column for current square
            int ajacent_row = row;
            int ajacent_column = column + 1;
            if (ajacent_column == DEFAULT_SIZE)
                ajacent_column = column - 1;

            // test each possible value of a square (lightbulb, mark, blank)
            for (uint iPlayableValue = 0; iPlayableValue < size_allPlayableValues; iPlayableValue++)
            {
                // test each possible value of the square being played on
                for (uint iSquare = 0; iSquare < size_allModifiableSquares; iSquare++)
                {
                    // test each posssible value of the ajacent square
                    // this is to modify the flags of the current square after the play move
                    for (uint iAjacentSquare = 0; iAjacentSquare < size_allAjacentSquares; iAjacentSquare++)
                    {
                        // set ajacent square
                        game_play_move(testGame, ajacent_row, ajacent_column, allAjacentSquares[iAjacentSquare]);
                        square ajacentSquareState = game_get_state(testGame, ajacent_row, ajacent_column);
                        // set current square
                        game_set_square(testGame, row, column, allModifiableSquares[iSquare]);

                        game_play_move(testGame, row, column, allPlayableValues[iPlayableValue]);

                        // check that the square has been modified
                        ASSERT(game_get_state(testGame, row, column) == allPlayableValues[iPlayableValue]);

                        // get the state and flag for the tests
                        square squareState = game_get_state(testGame, row, column);
                        square squareFlag = game_get_flags(testGame, row, column);

                        // check that flags for the square are correct
                        if (squareState == S_BLANK || squareState == S_MARK)
                        {
                            if (ajacentSquareState == S_BLANK)
                                ASSERT(squareFlag == S_BLANK);
                            else
                                ASSERT(squareFlag == F_LIGHTED);
                        }
                        else if (squareState == S_LIGHTBULB)
                        {
                            if (ajacentSquareState == S_BLANK)
                                ASSERT(squareFlag == F_LIGHTED);
                            else
                                ASSERT(squareFlag == (F_LIGHTED | F_ERROR));
                        }
                        else
                        {
                            fprintf(stderr, "[%s:%d] Error case: '%s'!\n", __FILE__, __LINE__, "Play move gave set square to incorrect value");
                            abort();
                        }
                    }

                    // reset the game to empty so next tests won't fail
                    game_delete(testGame);
                    testGame = game_new_empty();
                }
            }

            // reset the game to empty so next tests won't fail
            game_delete(testGame);
            testGame = game_new_empty();
        }
    }

    // clean up tests
    game_delete(testGame);
    return true;
}

/* ********** TEST GAME UPDATE FLAGS ********** */

bool test_game_update_flags()
{
    // [1] Test if adding lightbulbs works
    game testGame = game_new_empty();
    uint size_allPlayableValues = 7;
    square allPlayableValues[7] = {S_BLANK, S_MARK, S_LIGHTBULB, S_BLANK, S_LIGHTBULB, S_MARK, S_BLANK};

    // [a] Test if the rest of the map is blank
    for (uint row = 0; row < DEFAULT_SIZE; row++)
    {
        for (uint column = 0; column < DEFAULT_SIZE; column++)
        {

            for (uint i = 0; i < size_allPlayableValues; i++)
            {
                // play the square
                game_play_move(testGame, row, column, allPlayableValues[i]);
                // get the state and flags
                square squareState = game_get_state(testGame, row, column);
                square squareFlag = game_get_flags(testGame, row, column);

                // check the flags
                if (squareState == S_LIGHTBULB)
                    ASSERT(squareFlag == F_LIGHTED);
                else
                    ASSERT(squareFlag == S_BLANK);

                // check the flags of all the other
                for (uint i = 0; i < DEFAULT_SIZE; i++)
                {
                    ASSERT(game_get_flags(testGame, row, i) == squareFlag);
                    ASSERT(game_get_flags(testGame, i, column) == squareFlag);
                }
            }
        }
    }

    // [b] Test if the ajacent square is a lightbulb
    for (uint row = 0; row < DEFAULT_SIZE; row++)
    {
        for (uint column = 0; column < DEFAULT_SIZE; column++)
        {
            // calculate value of ajacent row and column for current square
            int ajacent_row = row;
            int ajacent_column = column + 1;
            if (ajacent_column == DEFAULT_SIZE)
                ajacent_column = column - 1;

            // set the ajacent square to a lightbulb
            game_play_move(testGame, ajacent_row, ajacent_column, S_LIGHTBULB);

            for (uint i = 0; i < size_allPlayableValues; i++)
            {
                // play the square
                game_play_move(testGame, row, column, allPlayableValues[i]);
                // get the state and flags
                square squareState = game_get_state(testGame, row, column);
                square squareFlag = game_get_flags(testGame, row, column);

                // check the flags
                if (squareState == S_LIGHTBULB)
                    ASSERT(squareFlag == (F_LIGHTED | F_ERROR));
                else
                    ASSERT(squareFlag == F_LIGHTED);

                // check the flags of all the other
                for (uint i = 0; i < DEFAULT_SIZE; i++)
                {
                    if (squareState == S_LIGHTBULB)
                    {
                        if (i == ajacent_column || i == column)
                            ASSERT(game_get_flags(testGame, row, i) == squareFlag);
                        else
                            ASSERT(game_get_flags(testGame, row, i) == F_LIGHTED);
                        if (i == ajacent_row || i == row)
                            ASSERT(game_get_flags(testGame, i, column) == squareFlag);
                        else
                            ASSERT(game_get_flags(testGame, i, column) == F_LIGHTED);
                    }
                    else
                    {
                        if (i == row)
                            ASSERT(game_get_flags(testGame, i, column) == F_LIGHTED);
                        else
                            ASSERT(game_get_flags(testGame, i, column) == S_BLANK);
                        ASSERT(game_get_flags(testGame, row, i) == F_LIGHTED);
                    }
                }
            }

            // remove the lightbulb from the ajacent square
            game_play_move(testGame, ajacent_row, ajacent_column, S_BLANK);
        }
    }

    // [2] Test if adding lightbulbs next to walls works
    for (uint row = 0; row < DEFAULT_SIZE; row++)
    {
        for (uint column = 0; column < DEFAULT_SIZE; column++)
        {
            // calculate value of ajacent row and column for current square
            int ajacent_row = row;
            int ajacent_column = column + 1;
            if (ajacent_column == DEFAULT_SIZE)
                ajacent_column = column - 1;

            // set square to wall without limit
            game_set_square(testGame, row, column, S_BLACKU);
            // set the ajacent square to a lightbulb
            game_play_move(testGame, ajacent_row, ajacent_column, S_LIGHTBULB);

            ASSERT(game_get_flags(testGame, row, column) == S_BLANK);

            // set the ajacent square to a blank
            game_play_move(testGame, ajacent_row, ajacent_column, S_BLANK);

            // set square to wall with limit
            game_set_square(testGame, row, column, S_BLACK0);
            // set the ajacent square to a lightbulb
            game_play_move(testGame, ajacent_row, ajacent_column, S_LIGHTBULB);

            ASSERT(game_get_flags(testGame, row, column) == F_ERROR);

            // remove the lightbulb from the ajacent square
            game_play_move(testGame, ajacent_row, ajacent_column, S_BLANK);
            // remove wall from square
            game_set_square(testGame, row, column, S_BLANK);
        }
    }

    // [3] Test that walls block light
    game_set_square(testGame, 0, 3, S_BLACK1);
    game_play_move(testGame, 0, 2, S_LIGHTBULB);
    ASSERT(game_get_square(testGame, 0, 2) == (S_LIGHTBULB | F_LIGHTED));
    ASSERT(game_get_square(testGame, 0, 3) == (S_BLACK1));
    ASSERT(game_get_square(testGame, 0, 0) == (F_LIGHTED));
    ASSERT(game_get_square(testGame, 0, 4) == (S_BLANK));
    ASSERT(game_get_square(testGame, 0, 5) == (S_BLANK));
    game_play_move(testGame, 0, 4, S_LIGHTBULB);
    ASSERT(game_get_square(testGame, 0, 3) == (S_BLACK1 | F_ERROR));
    ASSERT(game_get_square(testGame, 0, 4) == (S_LIGHTBULB | F_LIGHTED));
    ASSERT(game_get_square(testGame, 0, 5) == (F_LIGHTED));

    // [4] Test that all the walls can be errored
    game_delete(testGame);
    testGame = game_new_empty();

    // test wall 2
    game_set_square(testGame, 0, 3, S_BLACK2);
    game_play_move(testGame, 0, 2, S_LIGHTBULB);
    ASSERT(game_get_square(testGame, 0, 2) == (S_LIGHTBULB | F_LIGHTED));
    ASSERT(game_get_square(testGame, 0, 3) == (S_BLACK2));
    ASSERT(game_get_square(testGame, 0, 0) == (F_LIGHTED));
    ASSERT(game_get_square(testGame, 0, 4) == (S_BLANK));
    ASSERT(game_get_square(testGame, 0, 5) == (S_BLANK));
    game_play_move(testGame, 0, 4, S_LIGHTBULB);
    ASSERT(game_get_square(testGame, 0, 3) == (S_BLACK2));
    ASSERT(game_get_square(testGame, 0, 4) == (S_LIGHTBULB | F_LIGHTED));
    ASSERT(game_get_square(testGame, 0, 5) == (F_LIGHTED));
    game_play_move(testGame, 1, 3, S_LIGHTBULB);
    ASSERT(game_get_square(testGame, 0, 3) == (S_BLACK2 | F_ERROR));
    ASSERT(game_get_square(testGame, 1, 3) == (S_LIGHTBULB | F_LIGHTED));
    ASSERT(game_get_square(testGame, 2, 3) == (F_LIGHTED));

    game_delete(testGame);
    testGame = game_new_empty();

    // test wall 3
    game_set_square(testGame, 1, 3, S_BLACK3);
    game_play_move(testGame, 1, 2, S_LIGHTBULB);
    ASSERT(game_get_square(testGame, 1, 2) == (S_LIGHTBULB | F_LIGHTED));
    ASSERT(game_get_square(testGame, 1, 3) == (S_BLACK3));
    ASSERT(game_get_square(testGame, 1, 0) == (F_LIGHTED));
    ASSERT(game_get_square(testGame, 1, 4) == (S_BLANK));
    ASSERT(game_get_square(testGame, 1, 5) == (S_BLANK));
    game_play_move(testGame, 1, 4, S_LIGHTBULB);
    ASSERT(game_get_square(testGame, 1, 3) == (S_BLACK3));
    ASSERT(game_get_square(testGame, 1, 4) == (S_LIGHTBULB | F_LIGHTED));
    ASSERT(game_get_square(testGame, 1, 5) == (F_LIGHTED));
    game_play_move(testGame, 2, 3, S_LIGHTBULB);
    ASSERT(game_get_square(testGame, 1, 3) == (S_BLACK3));
    ASSERT(game_get_square(testGame, 2, 3) == (S_LIGHTBULB | F_LIGHTED));
    ASSERT(game_get_square(testGame, 3, 3) == (F_LIGHTED));
    game_play_move(testGame, 0, 3, S_LIGHTBULB);
    ASSERT(game_get_square(testGame, 1, 3) == (S_BLACK3 | F_ERROR));
    ASSERT(game_get_square(testGame, 2, 3) == (S_LIGHTBULB | F_LIGHTED));

    game_delete(testGame);
    return true;
}

/* ********** TEST GAME IS OVER ********** */

bool test_game_is_over()
{
    // [1] Test game default and default solution are correct
    game dafaultGame = game_default();
    game defaultSolutionGame = game_default_solution();
    ASSERT(!game_is_over(dafaultGame));
    ASSERT(game_is_over(defaultSolutionGame));
    game_delete(dafaultGame);
    game_delete(defaultSolutionGame);

    // [2] Test that for each square we can get correct value for game over for each possible value
    game testGame = game_new_empty();
    square *allSquares = create_array_all_values();

    // set new game to S_BLANK | F_LIGHTED to prevent other squares from interfering with tests
    for (uint row = 0; row < DEFAULT_SIZE; row++)
        for (uint column = 0; column < DEFAULT_SIZE; column++)
            game_set_square(testGame, row, column, S_BLANK | F_LIGHTED);

    // test each square
    for (uint row = 0; row < DEFAULT_SIZE; row++)
    {
        for (uint column = 0; column < DEFAULT_SIZE; column++)
        {
            // test each possible value of a square
            for (uint i = 0; i < SIZE_ALL_VALUES; i++)
            {
                // set the square to the starting value
                game_set_square(testGame, row, column, allSquares[i]);

                // check that if the square is valid the function returns true
                if (!(game_get_flags(testGame, row, column) & F_ERROR) && // no error and it is black or it is lighted
                    ((game_get_state(testGame, row, column) & S_BLACK) || (game_get_flags(testGame, row, column) & F_LIGHTED)))
                    ASSERT(game_is_over(testGame));
                else
                    ASSERT(!game_is_over(testGame));
            }

            // reset the square to blank lighted so other tests won't fail
            game_set_square(testGame, row, column, S_BLANK | F_LIGHTED);
        }
    }

    // clean up tests
    game_delete(testGame);
    free(allSquares);

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
    for (uint row = 0; row < DEFAULT_SIZE; row++)
    {
        for (uint column = 0; column < DEFAULT_SIZE; column++)
        {
            // for each possible value of a square
            for (uint i = 0; i < SIZE_ALL_VALUES; i++)
            {
                // set the square to the value and restart it
                game_set_square(testGame, row, column, allSquares[i]);
                // use state to test as in all situations the flags need to be removed
                square squareState = game_get_state(testGame, row, column);

                game_restart(testGame);

                // if it is black then check that it stays black else it should be blank
                if (squareState & S_BLACK)
                    ASSERT(game_get_square(testGame, row, column) == squareState);
                else
                    ASSERT(game_get_square(testGame, row, column) == S_BLANK);
            }

            // reset square to empty
            game_set_square(testGame, row, column, S_BLANK);
        }
    }

    // clean-up test game restart on each square for each value
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
