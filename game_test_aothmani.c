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

bool test_dummy()
{
  return true;
}
bool test_game_print()
{
  game mygame = game_new_empty();
  game_print(mygame);
  return true;
}

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

bool test_game_default_solution()
{
  game mydefaultgamesolution = game_default_solution();
  square array_solution[7*7]= {S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACK1,S_LIGHTBULB | F_LIGHTED, S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,
 S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLACK2,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,
 S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACKU,S_BLACK2,
 S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,
 S_BLACK1,S_BLACKU,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,
 S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACK2,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,
 S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED,S_BLACKU,S_BLANK | F_LIGHTED,S_BLANK | F_LIGHTED};
  for (int i=0;i<DEFAULT_SIZE;i++){
    for(int j=0;j<DEFAULT_SIZE;j++){
      
      ASSERT(game_get_square(mydefaultgamesolution, i, j) == array_solution[j + 7 * i]);
    }
  }
  return true ;
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
    ok =test_game_default_solution();
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
