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
    game g = game_new_empty();

    square array[7*7]= {S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK};

    square array_error[7*7]= {S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACKU,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLACK2,S_BLANK,S_BLANK,S_BLANK,S_BLANK};
    
    ASSERT(check_game(array,g));
    ASSERT(check_game(array_error,g) == false);
    return true;
}

/* ********** TEST GAME_COPY ********** */

bool test_game_copy(){
    game g = game_default();
    game g_sol = game_default_solution();

    game g_copy = game_copy(game_default());
    game g_copy_sol = game_copy(game_default_solution());

    ASSERT(g = g_copy);
    ASSERT(g_sol = g_copy_sol);
    return true;
}

/* ********** TEST GAME_EQUAL ********** */

bool test_game_equal(){
    game g1 = game_default();
    game g2 = game_default();
    game g3 = game_default_solution();

    ASSERT(game_equal(g1,g2));
    ASSERT(game_equal(g1,g3) == false);
    ASSERT(game_equal(g2,g3) == false);
    return true;
}

/* ********** TEST GAME_SET_SQUARE ********** */

bool test_game_set_square(){
    return true;
}

/* ********** TEST GAME_IS_BLACK ********** */

bool test_game_is_black(){
    square array [7*7]={S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,
    S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,
    S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,
    S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,
    S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,
    S_BLACK,S_BLACK0,S_BLACK1,S_BLACK};

    square array_error [7*7]={S_BLANK,S_LIGHTBULB,S_MARK,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,
    S_BLANK,S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,
    S_BLANK,S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,
    S_BLANK,S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK};
    
    game g = game_new(array);
    game g_error = game_new(array_error);
    for (int x = 0; x < 7; x++){
        for (int y = 0; y < 7;y++){
            bool not = game_is_black(g_error,x,y);
            bool good = game_is_black(g,x,y);
            ASSERT(good);
            ASSERT( not == false);
        }
    }
    return true;
}

/* ********** TEST GAME_GET_BLACK_NUMBER ********** */

bool test_game_get_black_number(){
    square array [7*7]={S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,
    S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,
    S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,
    S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,S_BLACK,S_BLACK,
    S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,
    S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
    S_BLACKU,S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK};
    game g = game_new(array);
    ASSERT(game_get_black_number(g,0,0) == 0);
    ASSERT(game_get_black_number(g,0,1) == 0);
    ASSERT(game_get_black_number(g,0,2) == 1);
    ASSERT(game_get_black_number(g,0,3) == 2);
    ASSERT(game_get_black_number(g,0,4) == 3);
    ASSERT(game_get_black_number(g,0,5) == 4);
    ASSERT(game_get_black_number(g,0,6) == -1);
    return true;
}

/* ********** TEST GAME_IS_MARKED********** */

bool test_game_is_marked(){
    square array_error [7*7]={S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,
    S_BLACK,S_BLACK,S_BLANK,S_LIGHTBULB,S_BLACK,S_BLANK,S_BLANK,
    S_BLANK,S_BLANK,S_BLACK,S_BLACK,S_BLANK,S_LIGHTBULB,S_BLACK,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK,S_BLACK,S_BLACK,
    S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,
    S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
    S_BLACKU,S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK};

    square array [7*7]={S_BLANK,S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
    S_LIGHTBULB,S_BLANK,S_BLANK,S_LIGHTBULB,S_BLACK,S_MARK,S_BLANK,
    S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,S_BLANK,S_LIGHTBULB,S_MARK,
    S_BLANK,S_BLANK,S_BLANK,S_MARK,S_LIGHTBULB,S_BLANK,S_BLANK,
    S_LIGHTBULB,S_MARK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_LIGHTBULB,
    S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK,S_BLACKU,S_MARK,
    S_BLACK,S_BLANK,S_BLACK,S_LIGHTBULB,S_MARK,S_BLACK,S_BLANK,};
    
    game g = game_new(array);
    game g_error = game_new(array_error);
    for (int x = 0; x < 7; x++){
        for (int y = 0; y < 7;y++){
            bool not = game_is_marked(g_error,x,y);
            ASSERT( not == false);
        }
    }
    ASSERT(game_is_marked(g,0,2));
    ASSERT(game_is_marked(g,1,5));
    ASSERT(game_is_marked(g,2,6));
    ASSERT(game_is_marked(g,3,3));
    ASSERT(game_is_marked(g,4,1));
    ASSERT(game_is_marked(g,5,6));
    ASSERT(game_is_marked(g,6,4));
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
