#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_aux.h"

/* ********** ASSERT ********** */

#define ASSERT(expr)                                                                        \
    do                                                                                      \
    {                                                                                       \
        if ((expr) == 0)                                                                    \
        {                                                                                   \
            fprintf(stderr, "[%s:%d] Assertion '%s' failed!\n", __FILE__, __LINE__, #expr); \
            abort();                                                                        \
        }                                                                                   \
    } while (0)

/* ********** TEST COMMUN ********** */

bool check_game(square *liste, game g){
    int gameWidth = DEFAULT_SIZE;
    int gameHeight = DEFAULT_SIZE;
    for (uint y = 0; y < gameHeight; y++)
    {
        for (uint x = 0; x < gameWidth; x++)
        {
            square carre = game_get_square(g, y, x);
            if (liste[x + gameWidth * y] != carre)
            {
                return false;
            }  
        }
    }
    return true;
}

/* ********** TEST game_new ********** */

bool test_game_new(){
    // game g = game_default();
    // game gsol = game_default_solution();

    square array[7*7]= {S_BLANK,S_BLANK,S_BLACK1,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK2,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACKU,S_BLACK2,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLACK1,S_BLACKU,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK2,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACKU,S_BLANK,S_BLANK};
    game g = game_new(array);

    square array_solution[7*7]= {S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACK1,S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,
    S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLACK2,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,
    S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACKU,S_BLACK2,
    S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,
    S_BLACK1,S_BLACKU,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,
    S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACK2,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,
    S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACKU,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED};
    game gsol = game_new(array_solution);

    square array_error[7*7]= {S_BLACK1,S_BLANK,S_BLACK1,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK2,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACKU,S_BLACK2,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLACK1,S_BLACKU,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK2,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACKU,S_BLANK,S_BLANK};

    ASSERT(check_game(array,g));
    ASSERT(check_game(array_solution,gsol));
    ASSERT(check_game(array_error,g) == false);

    return true;
}

/* ********** TEST GAME_NEW_EMPTY ********** */

bool test_game_new_empty(){
    return true;
}

/* ********** TEST GAME_COPY ********** */

bool test_game_copy(){
    return true;
}

/* ********** TEST GAME_EQUAL ********** */

bool test_game_equal(){
    return true;
}

/* ********** TEST GAME_SET_SQUARE ********** */

bool test_game_set_square(){
    return true;
}

/* ********** TEST GAME_IS_BLACK ********** */

bool test_game_is_black(){
    return true;
}

/* ********** TEST GAME_GET_BLACK_NUMBER ********** */

bool test_game_get_black_number(){
    return true;
}

/* ********** TEST GAME_IS_MARKED********** */

bool test_game_is_marked(){
    return true;
}

/* ********** TEST DUMMY ********** */

bool test_dummy(){
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
    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool ok = false;

    if (strcmp("dummy", argv[1]) == 0)
        ok = test_dummy(); 
    else if (strcmp("game_new", argv[1]) == 0)
        ok = test_game_new();
    else if (strcmp("game_new_empty", argv[1]) == 0)
        ok = test_game_new_empty();
    else if (strcmp("game_copy", argv[1]) == 0)
        ok = test_game_copy();
    else if (strcmp("game_equal", argv[1]) == 0)
        ok = test_game_equal();
    else if (strcmp("game_set_square", argv[1]) == 0)
        ok = test_game_set_square(); 
    else if (strcmp("game_is_black", argv[1]) == 0)
        ok = test_game_is_black(); 
    else if (strcmp("game_get_black_number", argv[1]) == 0)
        ok = test_game_get_black_number(); 
    else if (strcmp("game_is_marked", argv[1]) == 0)
        ok = test_game_is_marked(); 

    else
    {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }
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
