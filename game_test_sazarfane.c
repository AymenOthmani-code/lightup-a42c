#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.c"
#include "game.h"
#include "game_aux.h"
#include "game_test_commun.c"

/* ********** TEST game_new ********** */

bool test_game_new() {
    // Creation of arrays
    square *array_with_all = create_array_all_values();
    square array_element[DEFAULT_SIZE * DEFAULT_SIZE];
    for (int z = 0; z < SIZE_ALL_VALUES; z++) {
        for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
            // Fill array_elements with all the squares possible
            array_element[i] = array_with_all[z];
        }
        game game_test = game_new(array_element);
        // test every game corresponds to the array
        ASSERT(check_game(array_element, game_test));
        game_delete(game_test);
    }
    // clean-up test array
    free(array_with_all);
    return true;
}

/* ********** TEST GAME_NEW_EMPTY ********** */

bool test_game_new_empty() {
    // Create an empty game
    game game_test = game_new_empty();
    // Checks if S_BLANK array correponds to what is returned by game_new_empty
    for (int y = 0; y < DEFAULT_SIZE; y++) {
        for (int x = 0; x < DEFAULT_SIZE; x++) {
            ASSERT(game_get_square(game_test, x, y) == S_BLANK);
        }
    }
    // Clean up
    game_delete(game_test);
    return true;
}

/* ********** TEST GAME_COPY ********** */

bool test_game_copy() {
    // Creation of arrays
    square *array_with_all = create_array_all_values();
    square array_element[DEFAULT_SIZE * DEFAULT_SIZE];
    for (int z = 0; z < SIZE_ALL_VALUES; z++) {
        for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
            // Fill array_element
            array_element[i] = array_with_all[z];
        }
        game game_test = game_new(array_element);
        game game_test_copy = game_copy(game_test);
        // Test game
        ASSERT(game_equal(game_test, game_test_copy));
        game_delete(game_test);
        game_delete(game_test_copy);
    }

    // Clean up
    free(array_with_all);
    return true;
}

/* ********** TEST GAME_EQUAL ********** */

bool test_game_equal() {
    // Create array
    square *array_with_all = create_array_all_values();
    square array_element[DEFAULT_SIZE * DEFAULT_SIZE];

    // Create game_sol with game_default_solution
    game game_sol = game_default_solution();

    for (int z = 0; z < SIZE_ALL_VALUES; z++) {
        for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
            array_element[i] = array_with_all[z];
        }
        game game_test = game_new(array_element);
        game game_test_copy = game_copy(game_test);

        ASSERT(check_game(array_element, game_test));
        ASSERT(check_game(array_element, game_test_copy));
        ASSERT(game_equal(game_test, game_test_copy));
        ASSERT(!game_equal(game_test, game_sol));
        // Clean up
        game_delete(game_test);
        game_delete(game_test_copy);
    }

    // Test all possible values of each square
    game testGame = game_new_empty();
    game testGameTwo = game_new_empty();
    for (uint row = 0; row < DEFAULT_SIZE; row++) {
        for (uint column = 0; column < DEFAULT_SIZE; column++) {
            for (uint i = 0; i < SIZE_ALL_VALUES; i++) {
                game_set_square(testGame, row, column, array_with_all[i]);
                game_set_square(testGameTwo, row, column, array_with_all[i]);
                ASSERT(game_equal(testGame, testGameTwo));
            }
            game_set_square(testGame, row, column, S_BLANK);
            game_set_square(testGameTwo, row, column, S_BLANK);
            ASSERT(game_equal(testGame, testGameTwo));
        }
    }

    // Test that two instances of game_default and game_default_solution are
    // equal
    game new_default = game_default_solution();
    game new_def = game_default();
    game new_new_def = game_default();

    ASSERT(game_equal(game_sol, new_default));
    ASSERT(game_equal(new_def, new_new_def));

    game_delete(new_default);
    game_delete(new_def);
    game_delete(new_new_def);

    game_delete(testGame);
    game_delete(testGameTwo);

    // Check if it is not checking flags
    testGame = game_new_empty();
    testGameTwo = game_new_empty();

    game_set_square(testGame, 0, 0, S_BLANK);
    game_set_square(testGameTwo, 0, 0, (S_BLANK | F_LIGHTED));

    ASSERT(!game_equal(testGame, testGameTwo));

    // Check if it is not checking state
    testGame = game_new_empty();
    testGameTwo = game_new_empty();

    game_set_square(testGame, 0, 0, S_LIGHTBULB | F_LIGHTED);
    game_set_square(testGameTwo, 0, 0, (S_BLANK | F_LIGHTED));

    ASSERT(!game_equal(testGame, testGameTwo));

    // Check if heights are equal
    game g1 = game_new_empty_ext(5, 5, false);
    game g2 = game_new_empty_ext(4, 4, false);

    ASSERT(!game_equal(g1, g2));
    ASSERT(!game_equal(g2, g1));

    game g4 = game_new_empty_ext(5, 7, false);
    game g5 = game_new_empty_ext(7, 5, false);

    ASSERT(!game_equal(g4, g5));
    ASSERT(!game_equal(g5, g4));

    // Check if wrapping is set correctly
    game g3 = game_new_empty_ext(5, 5, true);

    ASSERT(!game_equal(g1, g3));

    // Clean up
    game_delete(testGame);
    game_delete(testGameTwo);
    game_delete(game_sol);
    free(array_with_all);
    return true;
}

/* ********** TEST GAME_SET_SQUARE ********** */

bool test_game_get_set_square() {
    // Create an empty_game
    game game_test = game_new_empty();
    // Recovers all array_values
    square *array_with_all = create_array_all_values();
    // Fill game_test with array_all_values
    for (int y = 0; y < DEFAULT_SIZE; y++) {
        for (int x = 0; x < DEFAULT_SIZE; x++) {
            for (int z = 0; z < SIZE_ALL_VALUES; z++) {
                game_set_square(game_test, x, y, array_with_all[z]);
                ASSERT(game_get_square(game_test, x, y) == array_with_all[z]);
            }
        }
    }
    free(array_with_all);
    game_delete(game_test);
    return true;
}

/* ********** TEST GAME_GET_STATE ********** */

bool test_game_get_state() {
    // Create an empty game
    game game_test = game_new_empty();
    square *array_with_all = create_array_all_values();
    square array_all_state[SIZE_ALL_VALUES] = {
        S_BLANK,  S_BLACK,     S_BLACK0,    S_BLACK1,    S_BLACK2,
        S_BLACK3, S_BLACK4,    S_BLACKU,    S_LIGHTBULB, S_MARK,
        S_BLANK,  S_LIGHTBULB, S_LIGHTBULB, S_MARK,      S_BLACK0,
        S_BLACK1, S_BLACK2,    S_BLACK3,    S_BLACK4,    S_BLACK};
    // Fill game_test with array_all_values
    for (int y = 0; y < DEFAULT_SIZE; y++) {
        for (int x = 0; x < DEFAULT_SIZE; x++) {
            for (int z = 0; z < SIZE_ALL_VALUES; z++) {
                game_set_square(game_test, x, y, array_with_all[z]);
                ASSERT(game_get_state(game_test, x, y) == array_all_state[z]);
            }
        }
    }
    game_delete(game_test);
    free(array_with_all);
    return true;
}

/* ********** TEST GAME_IS_BLACK ********** */

bool test_game_is_black() {
    // Create an array with black squares only
    int size_array_valid = 14;
    square array_valid[14] = {
        S_BLACK | F_ERROR,  S_BLACK0 | F_ERROR,
        S_BLACK1 | F_ERROR, S_BLACK2 | F_ERROR,
        S_BLACK3 | F_ERROR, S_BLACK4 | F_ERROR,
        S_BLACKU | F_ERROR, S_BLACK,
        S_BLACK0,           S_BLACK1,
        S_BLACK2,           S_BLACK3,
        S_BLACK4,           S_BLACKU,
    };

    // Create array with error
    int size_array_invalid = 7;
    square array_invalid[7] = {S_BLANK,
                               S_LIGHTBULB,
                               S_MARK,
                               S_BLANK | F_LIGHTED,
                               S_LIGHTBULB | F_LIGHTED,
                               S_LIGHTBULB | F_LIGHTED | F_ERROR,
                               S_MARK | F_LIGHTED};

    game game_test = game_new_empty();

    for (int x = 0; x < DEFAULT_SIZE; x++) {
        for (int y = 0; y < DEFAULT_SIZE; y++) {
            for (int i = 0; i < size_array_invalid; i++) {
                // Set square un square invalid et le test
                game_set_square(game_test, x, y, array_invalid[i]);
                ASSERT(!game_is_black(game_test, x, y));
            }
            for (int j = 0; j < size_array_valid; j++) {
                // Set square un square valide et le test
                game_set_square(game_test, x, y, array_valid[j]);
                ASSERT(game_is_black(game_test, x, y));
            }
        }
    }
    // Clean up
    game_delete(game_test);
    return true;
}

/* ********** TEST GAME_GET_BLACK_NUMBER ********** */

bool test_game_get_black_number() {
    // Create game
    game game_test = game_new_empty();
    // Create arrays
    int size_array = 5;
    square array_black[7] = {S_BLACKU, S_BLACK0, S_BLACK1,
                             S_BLACK2, S_BLACK3, S_BLACK4};
    square array_black_flags[7] = {S_BLACKU | F_ERROR, S_BLACK0 | F_ERROR,
                                   S_BLACK1 | F_ERROR, S_BLACK2 | F_ERROR,
                                   S_BLACK3 | F_ERROR, S_BLACK4 | F_ERROR};

    for (int x = 0; x < DEFAULT_SIZE; x++) {
        for (int y = 0; y < DEFAULT_SIZE; y++) {
            for (int z = -1; z < size_array; z++) {
                game_set_square(game_test, x, y, array_black[z + 1]);
                ASSERT(game_get_black_number(game_test, x, y) == z);
                game_set_square(game_test, x, y, array_black_flags[z + 1]);
                ASSERT(game_get_black_number(game_test, x, y) == z);
            }

            game_set_square(game_test, x, y, S_BLACK);
            ASSERT(game_get_black_number(game_test, x, y) == 0);

            game_set_square(game_test, x, y, S_BLACK | F_ERROR);
            ASSERT(game_get_black_number(game_test, x, y) == 0);
        }
    }
    // Clean up
    game_delete(game_test);
    return true;
}

/* ********** TEST GAME_IS_MARKED********** */

bool test_game_is_marked() {
    // Create an array with S_MARK squares
    int size_array_valid = 2;
    square array_valid[2] = {S_MARK, S_MARK | F_LIGHTED};
    // Create an array with every square except S_MARK square
    int size_array_invalid = 18;
    square array_invalid[18] = {S_BLACK,
                                S_BLACK0,
                                S_BLACK1,
                                S_BLACK2,
                                S_BLACK3,
                                S_BLACK4,
                                S_BLACKU,
                                S_LIGHTBULB,
                                S_BLANK | F_LIGHTED,
                                S_LIGHTBULB | F_LIGHTED,
                                S_LIGHTBULB | F_LIGHTED | F_ERROR,
                                S_BLANK,
                                S_BLACK0 | F_ERROR,
                                S_BLACK1 | F_ERROR,
                                S_BLACK2 | F_ERROR,
                                S_BLACK3 | F_ERROR,
                                S_BLACK4 | F_ERROR,
                                S_BLACK | F_ERROR};
    // Create 2 games
    game game_test = game_new_empty();

    for (int x = 0; x < DEFAULT_SIZE; x++) {
        for (int y = 0; y < DEFAULT_SIZE; y++) {
            for (int i = 0; i < size_array_invalid; i++) {
                // Met l'état invalide et test
                game_set_square(game_test, x, y, array_invalid[i]);
                ASSERT(!game_is_marked(game_test, x, y));
            }
            for (int j = 0; j < size_array_valid; j++) {
                // Met l'état invalide et test
                game_set_square(game_test, x, y, array_valid[j]);
                ASSERT(game_is_marked(game_test, x, y));
            }
        }
    }
    // Clean up
    game_delete(game_test);
    return true;
}

/* ********** TEST GAME_NEW_EXT********** */

bool test_game_new_ext() {
    // Create arrays
    square *array_with_all = create_array_all_values();

    for (int z = 0; z < SIZE_ALL_VALUES; z++) {
        for (int height = 1; height <= 10; height++) {
            for (int width = 1; width <= 10; width++) {
                square array_element[height * width];
                for (int i = 0; i < height * width; i++) {
                    // Fill array_element with all squares possible
                    array_element[i] = array_with_all[z];
                }
                game game_test =
                    game_new_ext(height, width, array_element, false);
                game game_test_wrapping =
                    game_new_ext(height, width, array_element, true);

                // Test if every game created correponds to the array
                ASSERT(check_game(array_element, game_test));
                ASSERT(check_game(array_element, game_test_wrapping));

                // Test height, width and wrapping (game_test)
                ASSERT(game_nb_cols(game_test) == width);
                ASSERT(game_nb_rows(game_test) == height);
                ASSERT(game_is_wrapping(game_test) == false);

                // Test height, width and wrapping (game_test_wrapping)
                ASSERT(game_nb_cols(game_test_wrapping) == width);
                ASSERT(game_nb_rows(game_test_wrapping) == height);
                ASSERT(game_is_wrapping(game_test_wrapping) == true);

                // Delete games
                game_delete(game_test);
                game_delete(game_test_wrapping);
            }
        }
    }

    // Clean-up test array
    free(array_with_all);
    return true;
}

/* ********** TEST GAME_NEW_EMPTY_EXT********** */

bool test_game_new_empty_ext() {
    for (int height = 1; height <= 10; height++) {
        for (int width = 1; width <= 10; width++) {
            game game_test = game_new_empty_ext(height, width, false);
            game game_test_wrapping = game_new_empty_ext(height, width, true);

            for (int y = 0; y < width; y++) {
                for (int x = 0; x < height; x++) {
                    ASSERT(game_get_square(game_test, x, y) == S_BLANK);
                    ASSERT(game_get_square(game_test_wrapping, x, y) ==
                           S_BLANK);
                }
            }

            // Test height, width and wrapping (game_test)
            ASSERT(game_nb_cols(game_test) == width);
            ASSERT(game_nb_rows(game_test) == height);
            ASSERT(game_is_wrapping(game_test) == false);

            // Test height, width and wrapping (game_test_wrapping)
            ASSERT(game_nb_cols(game_test_wrapping) == width);
            ASSERT(game_nb_rows(game_test_wrapping) == height);
            ASSERT(game_is_wrapping(game_test_wrapping) == true);

            // Delete games
            game_delete(game_test);
            game_delete(game_test_wrapping);
        }
    }
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
    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool ok = false;

    if (strcmp("game_new", argv[1]) == 0)
        ok = test_game_new();
    else if (strcmp("game_new_empty", argv[1]) == 0)
        ok = test_game_new_empty();
    else if (strcmp("game_copy", argv[1]) == 0)
        ok = test_game_copy();
    else if (strcmp("game_equal", argv[1]) == 0)
        ok = test_game_equal();
    else if (strcmp("game_set_square", argv[1]) == 0)
        ok = test_game_get_set_square();
    else if (strcmp("game_get_square", argv[1]) == 0)
        ok = test_game_get_set_square();
    else if (strcmp("game_get_state", argv[1]) == 0)
        ok = test_game_get_state();
    else if (strcmp("game_is_black", argv[1]) == 0)
        ok = test_game_is_black();
    else if (strcmp("game_get_black_number", argv[1]) == 0)
        ok = test_game_get_black_number();
    else if (strcmp("game_is_marked", argv[1]) == 0)
        ok = test_game_is_marked();
    else if (strcmp("game_new_ext", argv[1]) == 0)
        ok = test_game_new_ext();
    else if (strcmp("game_new_empty_ext", argv[1]) == 0)
        ok = test_game_new_empty_ext();
    else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (ok) {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}
