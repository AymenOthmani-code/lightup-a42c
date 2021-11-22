#include "game.h"
#include "game_aux.h"
#include "game_test_commun.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ********** TEST game_new ********** */

bool test_game_new() {
    // Création des arrays
    square *array_with_all = create_array_all_values();
    square array_element[DEFAULT_SIZE * DEFAULT_SIZE];
    for (int z = 0; z < SIZE_ALL_VALUES; z++) {
        for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
            // Remplis array_element avec tout les square possible
            array_element[i] = array_with_all[z];
        }
        game game_test = game_new(array_element);
        // test si chaque jeu crée correspond a l'array
        ASSERT(check_game(array_element, game_test));
        game_delete(game_test);
    }
    // clean-up test array
    free(array_with_all);
    return true;
}

/* ********** TEST GAME_NEW_EMPTY ********** */

bool test_game_new_empty() {
    // Création d'un jeu vide
    game game_test = game_new_empty();
    // Mon array de S_BLANK correspond à ce que devrai me renvoyé game_new_empty
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
    // Création des arrays
    square *array_with_all = create_array_all_values();
    square array_element[DEFAULT_SIZE * DEFAULT_SIZE];
    for (int z = 0; z < SIZE_ALL_VALUES; z++) {
        for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
            // Remplir array element
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
        // Effectue tout les tests
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

    // Clean up
    game_delete(testGame);
    game_delete(testGameTwo);
    game_delete(game_sol);
    free(array_with_all);
    return true;
}

/* ********** TEST GAME_SET_SQUARE ********** */

bool test_game_get_set_square() {
    // Création d'un jeu vide
    game game_test = game_new_empty();
    // Récupération array_all_values
    square *array_with_all = create_array_all_values();
    // Remplir de game_test avec les valeurs de array_all_values
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
    // Création d'un jeu vide
    game game_test = game_new_empty();
    square *array_with_all = create_array_all_values();
    square array_all_state[SIZE_ALL_VALUES] = {
        S_BLANK,  S_BLACK,     S_BLACK0,    S_BLACK1,    S_BLACK2,
        S_BLACK3, S_BLACK4,    S_BLACKU,    S_LIGHTBULB, S_MARK,
        S_BLANK,  S_LIGHTBULB, S_LIGHTBULB, S_MARK,      S_BLACK0,
        S_BLACK1, S_BLACK2,    S_BLACK3,    S_BLACK4,    S_BLACK};
    // Remplir de game_test avec les valeurs de array_all_values
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
    // Création d'array with all black
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
    // Création d'un jeu
    game game_test = game_new_empty();
    // Creation de mes array
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
            // Met S_BLACK et test
            game_set_square(game_test, x, y, S_BLACK);
            ASSERT(game_get_black_number(game_test, x, y) == 0);
            // Met S_BLACK | F_ERROR et test
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
    // Création d'un array avec des S_MARK placé au hasard
    int size_array_valid = 2;
    square array_valid[2] = {S_MARK, S_MARK | F_LIGHTED};
    // Création d'un array sans S_MARK mais avec tout les autres squares
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
    // Création des 2 games
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
    game_delete(game_test);
    return true;
}

/* ********** USAGE ********** */

void usage(int argc, char *argv[]) {
    fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[]) {
    if (argc == 1)
        usage(argc, argv);
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
