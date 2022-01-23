#define __USE_GNU
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_test_commun.c"

/* ********** TEST GAME CHECK MOVE ********** */

bool test_game_check_move() {
    // [1] Test that coordinates out of game returns false
    game newGame = game_new_empty();
    ASSERT(!game_check_move(newGame, DEFAULT_SIZE + 1, -1, S_BLANK));
    game_delete(newGame);

    // [2] Test that for each square we can play everything that is playable
    game testGame = game_new_empty();
    square *allSquares = create_array_all_values();

    // Test each square
    for (uint row = 0; row < DEFAULT_SIZE; row++) {
        for (uint column = 0; column < DEFAULT_SIZE; column++) {
            // Test each possible starting value of a square
            for (uint startingValue = 0; startingValue < SIZE_ALL_VALUES;
                 startingValue++) {
                // Set the square to the starting value
                game_set_square(testGame, row, column,
                                allSquares[startingValue]);

                // Get the current square for tests
                square currentSquare = game_get_square(testGame, row, column);

                // Check each possible move on the square
                for (uint testValue = 0; testValue < SIZE_ALL_VALUES;
                     testValue++) {
                    // If the square is not black and we are trying to add a
                    // blank, lightbulb or a mark check move needs to be true
                    if (!(currentSquare & S_BLACK) &&
                        ((allSquares[testValue] == S_BLANK) ||
                         (allSquares[testValue] == S_LIGHTBULB) ||
                         (allSquares[testValue] == S_MARK)))
                        ASSERT(game_check_move(testGame, row, column,
                                               allSquares[testValue]));
                    else
                        ASSERT(!game_check_move(testGame, row, column,
                                                allSquares[testValue]));
                }

                // Reset the square to blank
                game_set_square(testGame, row, column, S_BLANK);
            }
        }
    }

    // Clean up tests
    game_delete(testGame);
    free(allSquares);

    return true;
}

/* ********** TEST GAME PLAY MOVE ********** */

bool test_game_play_move() {
    // Test if square is set correctly for each possible value for every square
    game testGame = game_new_empty();
    uint size_allPlayableValues = 3;
    square allPlayableValues[3] = {S_BLANK, S_MARK, S_LIGHTBULB};
    uint size_allAjacentSquares = 2;
    square allAjacentSquares[2] = {S_BLANK, S_LIGHTBULB};
    uint size_allModifiableSquares = 7;
    square allModifiableSquares[7] = {S_BLANK,
                                      S_LIGHTBULB,
                                      S_MARK,
                                      S_BLANK | F_LIGHTED,
                                      S_LIGHTBULB | F_LIGHTED,
                                      S_LIGHTBULB | F_LIGHTED | F_ERROR,
                                      S_MARK | F_LIGHTED};

    // Test each square
    for (uint row = 0; row < DEFAULT_SIZE; row++) {
        for (uint column = 0; column < DEFAULT_SIZE; column++) {
            // Calculate value of ajacent row and column for current square
            int ajacent_row = row;
            int ajacent_column = column + 1;
            if (ajacent_column == DEFAULT_SIZE) ajacent_column = column - 1;

            // Test each possible value of a square (lightbulb, mark, blank)
            for (uint iPlayableValue = 0;
                 iPlayableValue < size_allPlayableValues; iPlayableValue++) {
                // Test each possible value of the square being played on
                for (uint iSquare = 0; iSquare < size_allModifiableSquares;
                     iSquare++) {
                    // Test each posssible value of the ajacent square
                    // this is to modify the flags of the current square after
                    // the play move
                    for (uint iAjacentSquare = 0;
                         iAjacentSquare < size_allAjacentSquares;
                         iAjacentSquare++) {
                        // Set ajacent square
                        game_play_move(testGame, ajacent_row, ajacent_column,
                                       allAjacentSquares[iAjacentSquare]);
                        square ajacentSquareState = game_get_state(
                            testGame, ajacent_row, ajacent_column);
                        // Set current square
                        game_set_square(testGame, row, column,
                                        allModifiableSquares[iSquare]);

                        game_play_move(testGame, row, column,
                                       allPlayableValues[iPlayableValue]);

                        // Check that the square has been modified
                        ASSERT(game_get_state(testGame, row, column) ==
                               allPlayableValues[iPlayableValue]);

                        // Get the state and flag for the tests
                        square squareState =
                            game_get_state(testGame, row, column);
                        square squareFlag =
                            game_get_flags(testGame, row, column);

                        // Check that flags for the square are correct
                        if (squareState == S_BLANK || squareState == S_MARK) {
                            if (ajacentSquareState == S_BLANK)
                                ASSERT(squareFlag == S_BLANK);
                            else
                                ASSERT(squareFlag == F_LIGHTED);
                        } else if (squareState == S_LIGHTBULB) {
                            if (ajacentSquareState == S_BLANK)
                                ASSERT(squareFlag == F_LIGHTED);
                            else
                                ASSERT(squareFlag == (F_LIGHTED | F_ERROR));
                        } else {
                            fprintf(
                                stderr, "[%s:%d] Error case: '%s'!\n", __FILE__,
                                __LINE__,
                                "Play move gave set square to incorrect value");
                            abort();
                        }
                    }

                    // Reset the game to empty so next tests won't fail
                    game_delete(testGame);
                    testGame = game_new_empty();
                }
            }

            // Reset the game to empty so next tests won't fail
            game_delete(testGame);
            testGame = game_new_empty();
        }
    }

    // Clean up tests
    game_delete(testGame);
    return true;
}

/* ********** TEST GAME UPDATE FLAGS ********** */

bool test_update_flag_default() {
    // [0] Test provided
    // Test lighted flags (default solution)
    game g0 = game_default();
    game_set_square(g0, 0, 0, S_LIGHTBULB);
    game_set_square(g0, 1, 1, S_LIGHTBULB);
    game_set_square(g0, 2, 2, S_LIGHTBULB);
    game_set_square(g0, 0, 3, S_LIGHTBULB);
    game_set_square(g0, 1, 6, S_LIGHTBULB);
    game_set_square(g0, 3, 6, S_LIGHTBULB);
    game_set_square(g0, 4, 4, S_LIGHTBULB);
    game_set_square(g0, 5, 0, S_LIGHTBULB);
    game_set_square(g0, 5, 5, S_LIGHTBULB);
    game_set_square(g0, 6, 1, S_LIGHTBULB);
    game_update_flags(g0);

    game g1 = game_default_solution();

    ASSERT(game_equal(g0, g1));

    game_delete(g0);
    game_delete(g1);

    // Test error flags both on lightbulb and black wall
    game g2 = game_default();
    game_set_square(g2, 0, 0, S_LIGHTBULB);
    game_set_square(g2, 3, 0, S_LIGHTBULB);  // error flags on ligthbulbs (0,0)
                                             // and (3,0) and black wall (2,6)
    game_set_square(g2, 6, 6, S_MARK);
    game_set_square(g2, 0, 6, S_LIGHTBULB);
    game_set_square(g2, 0, 6, S_BLANK);
    game_update_flags(g2);

    game g3 = game_default_other();

    ASSERT(game_equal(g2, g3));

    game_delete(g2);
    game_delete(g3);

    return true;
}

bool test_update_flag_play_move() {
    // [1] Test if adding lightbulbs works
    game testGame = game_new_empty();
    uint size_allPlayableValues = 7;
    square allPlayableValues[7] = {S_BLANK,     S_MARK, S_LIGHTBULB, S_BLANK,
                                   S_LIGHTBULB, S_MARK, S_BLANK};

    // [a] Test if the ajacent rows and colums have the proper flags after
    // playing a move
    for (uint row = 0; row < DEFAULT_SIZE; row++) {
        for (uint column = 0; column < DEFAULT_SIZE; column++) {
            for (uint i = 0; i < size_allPlayableValues; i++) {
                // Play the square
                game_play_move(testGame, row, column, allPlayableValues[i]);
                // Get the state and flags
                square squareState = game_get_state(testGame, row, column);
                square squareFlag = game_get_flags(testGame, row, column);

                // Check the flags
                if (squareState == S_LIGHTBULB)
                    ASSERT(squareFlag == F_LIGHTED);
                else
                    ASSERT(squareFlag == S_BLANK);

                // Check the flags of all the other
                for (uint i = 0; i < DEFAULT_SIZE; i++) {
                    ASSERT(game_get_flags(testGame, row, i) == squareFlag);
                    ASSERT(game_get_flags(testGame, i, column) == squareFlag);
                }
            }
        }
    }

    // [b] Test if the ajacent rows and colums have the proper flags after
    // playing a move if an ajacent square is a lightbulb
    for (uint row = 0; row < DEFAULT_SIZE; row++) {
        for (uint column = 0; column < DEFAULT_SIZE; column++) {
            // Calculate value of ajacent row and column for current square
            int ajacent_row = row;
            int ajacent_column = column + 1;
            if (ajacent_column == DEFAULT_SIZE) ajacent_column = column - 1;

            // Set the ajacent square to a lightbulb
            game_play_move(testGame, ajacent_row, ajacent_column, S_LIGHTBULB);

            for (uint i = 0; i < size_allPlayableValues; i++) {
                game_play_move(testGame, row, column, allPlayableValues[i]);
                // Get the state and flags
                square squareState = game_get_state(testGame, row, column);
                square squareFlag = game_get_flags(testGame, row, column);

                // Check the flags
                if (squareState == S_LIGHTBULB)
                    ASSERT(squareFlag == (F_LIGHTED | F_ERROR));
                else
                    ASSERT(squareFlag == F_LIGHTED);

                // Check the flags of the ajacent rows and colums
                for (uint i = 0; i < DEFAULT_SIZE; i++) {
                    if (squareState == S_LIGHTBULB) {
                        if (i == ajacent_column || i == column)
                            ASSERT(game_get_flags(testGame, row, i) ==
                                   squareFlag);
                        else
                            ASSERT(game_get_flags(testGame, row, i) ==
                                   F_LIGHTED);
                        if (i == ajacent_row || i == row)
                            ASSERT(game_get_flags(testGame, i, column) ==
                                   squareFlag);
                        else
                            ASSERT(game_get_flags(testGame, i, column) ==
                                   F_LIGHTED);
                    } else {
                        if (i == row)
                            ASSERT(game_get_flags(testGame, i, column) ==
                                   F_LIGHTED);
                        else
                            ASSERT(game_get_flags(testGame, i, column) ==
                                   S_BLANK);
                        ASSERT(game_get_flags(testGame, row, i) == F_LIGHTED);
                    }
                }
            }

            // Remove the lightbulb from the ajacent square
            game_play_move(testGame, ajacent_row, ajacent_column, S_BLANK);
        }
    }
    game_delete(testGame);
    return true;
}

bool test_update_flag_walls() {
    // [2] Test if adding lightbulbs next to walls works
    game testGame = game_new_empty();
    for (uint row = 0; row < DEFAULT_SIZE; row++) {
        for (uint column = 0; column < DEFAULT_SIZE; column++) {
            // calculate value of ajacent row and column for current square
            int ajacent_row = row;
            int ajacent_column = column + 1;
            if (ajacent_column == DEFAULT_SIZE) ajacent_column = column - 1;

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
    game_delete(testGame);
    return true;
}

bool test_walls_block_light() {
    // [3] Test that walls block light
    game testGame = game_new_empty();
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

    game_delete(testGame);
    return true;
}

bool test_walls_errored() {
    game testGame = game_new_empty();
    // [4] Test that all the walls can be errored
    // Test wall 2
    game_set_square(testGame, 0, 3, S_BLACK2);
    // Add lightbulbs and ensure the ajacent squares are correct
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

    // Test wall 3
    game_set_square(testGame, 1, 3, S_BLACK3);
    // Add lightbulbs and ensure the ajacent squares are correct
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

bool test_lightbulb_error() {
    game testGame = game_new_empty();

    // [5] Test that lightbulb can cause error on far walls
    game_set_square(testGame, 3, 2, S_BLACK3);
    game_set_square(testGame, 3, 3, S_BLACKU);
    game_play_move(testGame, 3, 0, S_LIGHTBULB);

    ASSERT(game_get_square(testGame, 3, 2) == (S_BLACK3 | F_ERROR));

    game_delete(testGame);

    return true;
}

bool test_wrapping() {
    // [6] Test wrapping
    game testGame = game_new_empty_ext(5, 3, true);

    game_set_square(testGame, 1, 0, S_BLACKU);
    game_set_square(testGame, 2, 1, S_BLACK2);
    game_set_square(testGame, 1, 2, S_BLACK1);

    game_play_move(testGame, 1, 1, S_LIGHTBULB);
    game_play_move(testGame, 2, 0, S_LIGHTBULB);
    game_play_move(testGame, 3, 2, S_LIGHTBULB);

    ASSERT(game_is_over(testGame));

    game_delete(testGame);
    return true;
}

bool test_game_update_flags() {
    ASSERT(test_update_flag_default());
    ASSERT(test_update_flag_play_move());
    ASSERT(test_update_flag_walls());
    ASSERT(test_walls_block_light());
    ASSERT(test_walls_errored());
    ASSERT(test_lightbulb_error());
    ASSERT(test_wrapping());

    return true;
}

/* ********** TEST GAME IS OVER ********** */

bool test_game_is_over() {
    // [1] Test game default and default solution are correct
    game dafaultGame = game_default();
    game defaultSolutionGame = game_default_solution();

    ASSERT(!game_is_over(dafaultGame));
    ASSERT(game_is_over(defaultSolutionGame));

    game_delete(dafaultGame);
    game_delete(defaultSolutionGame);

    // [2] Test that for each square we can get correct value for game over for
    // each possible value
    game testGame = game_new_empty();
    square *allSquares = create_array_all_values();

    // Set new game to S_BLANK | F_LIGHTED to prevent other squares from
    // interfering with tests
    for (uint row = 0; row < DEFAULT_SIZE; row++)
        for (uint column = 0; column < DEFAULT_SIZE; column++)
            game_set_square(testGame, row, column, S_BLANK | F_LIGHTED);

    // Test each square
    for (uint row = 0; row < DEFAULT_SIZE; row++) {
        for (uint column = 0; column < DEFAULT_SIZE; column++) {
            // Test each possible value of a square
            for (uint i = 0; i < SIZE_ALL_VALUES; i++) {
                // Set the square to the starting value
                game_set_square(testGame, row, column, allSquares[i]);

                // Check that if the square is valid the function returns true
                if (!(game_get_flags(testGame, row, column) &
                      F_ERROR) &&  // No error and it is black or it is lighted
                    ((game_get_state(testGame, row, column) & S_BLACK) ||
                     (game_get_flags(testGame, row, column) & F_LIGHTED)))
                    ASSERT(game_is_over(testGame));
                else
                    ASSERT(!game_is_over(testGame));
            }

            // Reset the square to blank lighted so other tests won't fail
            game_set_square(testGame, row, column, S_BLANK | F_LIGHTED);
        }
    }

    // Clean up tests
    game_delete(testGame);
    free(allSquares);

    return true;
}

/* ********** TEST GAME RESTART ********** */

bool test_game_restart() {
    // [1] Test game default and game default solution
    game gameDefault = game_default();
    game gameDefaultSolution = game_default_solution();

    game_restart(gameDefaultSolution);

    // Restarting game default solution should give game default
    ASSERT(game_equal(gameDefault, gameDefaultSolution));

    game_delete(gameDefault);
    game_delete(gameDefaultSolution);

    // [2] Test of game restart on each square for each value
    square *allSquares = create_array_all_values();
    game testGame = game_new_empty();

    // Test each square
    for (uint row = 0; row < DEFAULT_SIZE; row++) {
        for (uint column = 0; column < DEFAULT_SIZE; column++) {
            // For each possible value of a square
            for (uint i = 0; i < SIZE_ALL_VALUES; i++) {
                // Set the square to the value and restart it
                game_set_square(testGame, row, column, allSquares[i]);
                // Use state to test as in all situations the flags need to be
                // removed
                square squareState = game_get_state(testGame, row, column);

                game_restart(testGame);

                // If it is black then check that it stays black else it should
                // be blank
                if (squareState & S_BLACK)
                    ASSERT(game_get_square(testGame, row, column) ==
                           squareState);
                else
                    ASSERT(game_get_square(testGame, row, column) == S_BLANK);
            }

            // Reset square to empty
            game_set_square(testGame, row, column, S_BLANK);
        }
    }

    // [3] Test undo
    square S_moov[3] = {S_MARK, S_LIGHTBULB, S_BLANK};

    game testGameTwo = game_new_empty();

    for (uint row = 0; row < DEFAULT_SIZE; row++) {
        for (uint column = 0; column < DEFAULT_SIZE; column++) {
            // For each possible value of a square
            for (uint i = 0; i < 2; i++) {
                game_play_move(testGameTwo, row, column, S_moov[i]);
                ASSERT(game_get_state(testGameTwo, row, column) == S_moov[i]);
                game_restart(testGameTwo);
                ASSERT(game_get_state(testGameTwo, row, column) == S_BLANK);
                game_undo(testGameTwo);
                ASSERT(game_get_state(testGameTwo, row, column) == S_BLANK);
            }
        }
    }

    // [4] Test redo
    game testGameThree = game_new_empty();

    for (uint row = 0; row < DEFAULT_SIZE; row++) {
        for (uint column = 0; column < DEFAULT_SIZE; column++) {
            // For each possible value of a square
            for (uint i = 0; i < 2; i++) {
                game_play_move(testGameThree, row, column, S_moov[i]);
                ASSERT(game_get_state(testGameThree, row, column) == S_moov[i]);
                game_restart(testGameThree);
                ASSERT(game_get_state(testGameThree, row, column) == S_BLANK);
                game_redo(testGameThree);
                ASSERT(game_get_state(testGameThree, row, column) == S_BLANK);
            }
        }
    }

    // Clean-up test game restart on each square for each value
    free(allSquares);
    game_delete(testGameTwo);
    game_delete(testGameThree);

    return true;
}

/* ********** TEST game_undo_redo ********** */

bool test_game_undo_redo() {
    // Create game
    game gameTest = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false);
    game gameEmpty = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false);

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0; j < DEFAULT_SIZE; j++) {
            // Check undo / redo for S_LIGHTBULB
            game_play_move(gameTest, i, j, S_LIGHTBULB);
            ASSERT(game_get_state(gameTest, i, j) == S_LIGHTBULB);
            game_undo(gameTest);
            ASSERT(game_get_state(gameTest, i, j) == S_BLANK);
            game_redo(gameTest);
            ASSERT(game_get_state(gameTest, i, j) == S_LIGHTBULB);

            // Check undo / redo for S_MARK
            game_play_move(gameTest, i, j, S_MARK);
            ASSERT(game_get_state(gameTest, i, j) == S_MARK);
            game_undo(gameTest);
            ASSERT(game_get_state(gameTest, i, j) == S_LIGHTBULB);
            game_redo(gameTest);
            ASSERT(game_get_state(gameTest, i, j) == S_MARK);

            // Check undo / redo for S_BLANK
            game_play_move(gameTest, i, j, S_LIGHTBULB);
            ASSERT(game_get_state(gameTest, i, j) == S_LIGHTBULB);
            game_play_move(gameTest, i, j, S_BLANK);
            ASSERT(game_get_state(gameTest, i, j) == S_BLANK);
            game_undo(gameTest);
            ASSERT(game_get_state(gameTest, i, j) == S_LIGHTBULB);
            game_redo(gameTest);
            ASSERT(game_get_state(gameTest, i, j) == S_BLANK);
        }
    }

    // Play two moves and undo one move
    game_play_move(gameEmpty, 0, 0, S_LIGHTBULB);
    ASSERT(game_get_state(gameEmpty, 0, 0) == S_LIGHTBULB);

    game_play_move(gameEmpty, 0, 1, S_LIGHTBULB);
    ASSERT(game_get_state(gameEmpty, 0, 1) == S_LIGHTBULB);

    game_undo(gameEmpty);
    ASSERT(game_get_state(gameEmpty, 0, 0) == S_LIGHTBULB);
    ASSERT(game_get_state(gameEmpty, 0, 1) == S_BLANK);

    // Make sure playing a move clears the redo history
    game_play_move(gameEmpty, 0, 2, S_MARK);
    ASSERT(game_get_state(gameEmpty, 0, 2) == S_MARK);

    game_redo(gameEmpty);
    ASSERT(game_get_state(gameEmpty, 0, 0) == S_LIGHTBULB);
    ASSERT(game_get_state(gameEmpty, 0, 1) == S_BLANK);
    ASSERT(game_get_state(gameEmpty, 0, 2) == S_MARK);

    // Clean up
    game_delete(gameTest);
    game_delete(gameEmpty);

    return true;
}

/* ********** USAGE ********** */

void usage(int argc, char *argv[]) {
    fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[]) {
    if (argc == 1) usage(argc, argv);

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
    else if (strcmp("game_undo", argv[1]) == 0)
        ok = test_game_undo_redo();
    else if (strcmp("game_redo", argv[1]) == 0)
        ok = test_game_undo_redo();
    else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // print test result
    if (ok) {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
} 