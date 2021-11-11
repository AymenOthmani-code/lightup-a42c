#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"

/* ********** ASSERT ********** */

#define ASSERT(expr)                                                                  \
  do                                                                                  \
  {                                                                                   \
    if ((expr) == 0)                                                                  \
    {                                                                                 \
      fprintf(stderr, "[%s:%d] Assertion '%s' failed!\n", __FILE__, __LINE__, #expr); \
      abort();                                                                        \
    }                                                                                 \
  } while (0)
/* ********** TEST dummy********** */
bool test_dummy()
{
  return true;
}

/* ********** TEST game_print ********** */

bool test_game_print()
{
  game mygame = game_new_empty();
  game_print(mygame);
  return true;
}

/* ********** TEST game_default ********** */

bool test_game_default()
{
  game mydefaultgame = game_default();
  square array[7 * 7] = {S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};

  for (int i = 0; i < DEFAULT_SIZE; i++)
  {
    for (int j = 0; j < DEFAULT_SIZE; j++)
    {
      ASSERT(game_get_square(mydefaultgame, i, j) == array[j + DEFAULT_SIZE * i]);
    }
  }
  return true;
}

/* ********** TEST game_default_solution ********** */

bool test_game_default_solution()
{
  game mydefaultgamesolution = game_default_solution();
  square array_solution[7 * 7] = {S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLACK1, S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED,
                                  S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED, S_BLACK2, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED,
                                  S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLACKU, S_BLACK2,
                                  S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED,
                                  S_BLACK1, S_BLACKU, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED,
                                  S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLACK2, S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED,
                                  S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLACKU, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED};
  for (int i = 0; i < DEFAULT_SIZE; i++)
  {
    for (int j = 0; j < DEFAULT_SIZE; j++)
    {

      ASSERT(game_get_square(mydefaultgamesolution, i, j) == array_solution[j + 7 * i]);
    }
  }
  return true;
}

/* ********** TEST game_delete********** */

bool test_game_delete()
{
  game g = game_default();
  game_delete(g);
  return true;
}

/* ********** TEST game_is_blank ********** */

bool test_game_is_blank()
{
  square array[7 * 7] = {S_BLANK, S_LIGHTBULB, S_MARK, S_BLACK0, S_BLACK1, S_BLACK2, S_BLACK3,
                         S_BLACK4, S_BLACKU, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};
 
  square array_error[7 * 7] = {S_BLACK, S_BLACK0, S_BLACK1, S_BLACK2, S_MARK, S_BLACK4, S_BLACKU, S_BLACK, S_BLACK,
                               S_BLACK, S_BLACK0, S_BLACK1, S_BLACK2, S_BLACK3, S_BLACK4, S_BLACKU, S_BLACK, S_BLACK,
                               S_BLACK, S_BLACK1, S_BLACK2, S_BLACK3, S_BLACK4, S_LIGHTBULB, S_BLACK, S_BLACK,
                               S_BLACK, S_BLACK0, S_BLACK1, S_LIGHTBULB, S_BLACK3, S_BLACK4, S_BLACKU, S_BLACK, S_MARK,
                               S_BLACK, S_BLACK0, S_MARK, S_BLACK2, S_BLACK3, S_BLACK4, S_BLACKU, S_BLACK3, S_BLACK,
                               S_BLACK, S_BLACK0, S_BLACK1, S_BLACK,S_LIGHTBULB};
  game g = game_new(array);
  game g_error = game_new(array_error);

  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      bool not = game_is_blank(g_error, i, j);
      ASSERT(not == false);
    }
  }
  ASSERT(game_is_blank(g, 0, 0));
  return true;
}

/* ********** TEST game_get_square ********** */

bool test_game_get_square()
{
  square array[7 * 7] = {S_BLANK, S_LIGHTBULB, S_MARK, S_BLACK0, S_BLACK1, S_BLACK2, S_BLACK3,
                         S_BLACK4, S_BLACKU, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_LIGHTBULB, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};
  game g = game_new(array);
  for (unsigned int i = 0; i < DEFAULT_SIZE; i++)
  {
    for (unsigned int j = 0; j < DEFAULT_SIZE; j++)
    {
      ASSERT(game_get_square(g,i,j)==array[j + 7 * i]);
    }
  }
  return true;
}
/* ********** TEST game_is_lightbulb ********** */

bool test_game_is_lightbulb()
{
    square array[7*7]= {
        S_LIGHTBULB,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_LIGHTBULB,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK
        };
    square array_error [7*7]={
        S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,
        S_BLACK,S_BLACK,S_BLANK,S_MARK,S_BLACK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_BLACK,S_BLACK,S_BLANK,S_MARK,S_BLACK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        S_BLACKU,S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK
    };
    game g = game_new(array);
    game g_error = game_new(array_error);
    for (int x = 0; x < 7; x++){
        for (int y = 0; y < 7;y++){
            ASSERT( game_is_lightbulb(g_error,x,y) == false); 
        }
    }
    ASSERT(game_is_lightbulb(g,0,0));
    ASSERT(game_is_lightbulb(g,5,4));
    return true;
}

/* ********** TEST game_is_lighted ********** */

bool test_game_is_lighted()
{
  square array[7 * 7] = {S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLACK1, S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED,
                                  S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED, S_BLACK2, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED,
                                  S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLACKU, S_BLACK2,
                                  S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLACK1 | F_LIGHTED, S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED,
                                  S_BLACK1, S_BLACKU, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED,
                                  S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLACK2, S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED,
                                  S_BLANK | F_LIGHTED, S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED, S_BLACKU, S_BLANK | F_LIGHTED, S_BLANK | F_LIGHTED};
square array_error [7*7]={
        S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,
        S_BLACK,S_BLACK,S_BLANK,S_MARK,S_BLACK,S_BLANK,S_BLANK,
        S_BLANK,S_BLANK,S_LIGHTBULB,S_BLACK,S_BLANK,S_MARK,S_BLACK,
        S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLACK,S_BLACK,S_BLACK,
        S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_BLACK,
        S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,
        S_BLACKU,S_BLACK,S_BLACK,S_BLACK,S_BLACK0,S_BLACK1,S_LIGHTBULB
    };
game g = game_new(array);
game g_error = game_new(array_error);
 for (int x = 0; x < 7; x++){
        for (int y = 0; y < 7;y++){
            ASSERT( game_is_lighted(g_error,x,y) == false); 
        }
    }
    ASSERT(game_is_lighted(g,0,0));
    return true;


}

void usage(int argc, char *argv[])
{
  fprintf(stderr, "Usage: %s <dummy> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    usage(argc, argv);
  }
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  bool ok = false;

  if (strcmp("dummy", argv[1]) == 0)
    ok = test_dummy();
  else if (strcmp("game_print", argv[1]) == 0)
    ok = test_game_print();
  else if (strcmp("game_default", argv[1]) == 0)
    ok = test_game_default();
  else if (strcmp("game_default_solution", argv[1]) == 0)
    ok = test_game_default_solution();
  else if (strcmp("game_delete", argv[1]) == 0)
    ok = test_game_delete();
  else if (strcmp("game_is_blank", argv[1]) == 0)
    ok = test_game_is_blank();
  else if (strcmp("game_get_square", argv[1]) == 0)
    ok = test_game_get_square();
  else if (strcmp("game_is_lightbulb", argv[1]) == 0)
    ok = test_game_is_lightbulb();
  else if (strcmp("game_is_lighted", argv[1]) == 0)
    ok = test_game_is_lighted();
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
