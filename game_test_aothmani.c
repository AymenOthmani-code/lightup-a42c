#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_test_commun.c"

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
  square array[DEFAULT_SIZE * DEFAULT_SIZE] = {S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
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
  square array[DEFAULT_SIZE * DEFAULT_SIZE] = {S_BLANK, S_BLANK, S_BLACK1, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLACK2,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLACK1, S_BLACKU, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACK2, S_BLANK, S_BLANK,
                         S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLACKU, S_BLANK, S_BLANK};
  game new_game = game_new(array);
  for (int height = 0; height < DEFAULT_SIZE; height++)
  {
    for (int width = 0; width < DEFAULT_SIZE; width++)
    {
      if ((game_get_square(mydefaultgamesolution, height, width) == S_BLACK) || (game_get_square(mydefaultgamesolution, height, width) == S_BLACK1) ||
          (game_get_square(mydefaultgamesolution, height, width) == S_BLACK2) || (game_get_square(mydefaultgamesolution, height, width) == S_BLACK3) ||
          (game_get_square(mydefaultgamesolution, height, width) == S_BLACK4) || (game_get_square(mydefaultgamesolution, height, width) == S_BLACKU))
      {
        ASSERT(game_get_square(mydefaultgamesolution, height, width) == (game_get_square(new_game, height, width)));
      }
    }
  }
  return true;
  ASSERT(game_is_over(mydefaultgamesolution));
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
  // Creating an array with only blank square
  square blank_array[2] = {S_BLANK, S_BLANK|F_LIGHTED};

  // Creating an array with every square type possible other then blank
  square array_error[19] = {
        S_BLACK | F_ERROR,S_BLACK0 | F_ERROR,S_BLACK1 | F_ERROR,S_BLACK2 | F_ERROR,S_BLACK3 | F_ERROR,S_BLACK4 | F_ERROR,S_BLACKU | F_ERROR,
        S_BLACK,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU, S_LIGHTBULB, S_MARK|F_LIGHTED,S_MARK,S_BLACK0, S_LIGHTBULB | F_LIGHTED | F_ERROR ,S_MARK | F_LIGHTED
        };;

  // Creating a game to test 
  game game_test = game_new_empty();

  for (int height = 0; height < DEFAULT_SIZE; height++)
  {
    for (int width = 0; width < DEFAULT_SIZE; width++)
    {
      for (int i = 0; i<19;i++){
                game_set_square(game_test,height,width,array_error[i]);
                ASSERT(!game_is_blank(game_test,height,width));
            }
            for (int j = 0; j<2;j++){
                game_set_square(game_test,height,width,blank_array[j]);
                ASSERT(game_is_blank(game_test,height,width)); 
            }
    }
  }
  return true;
}

/* ********** TEST game_is_lightbulb ********** */

bool test_game_is_lightbulb()
{
  // Creating an array with only lightbulb square
  square lightbulb_array[2] = {S_LIGHTBULB, S_LIGHTBULB | F_LIGHTED | F_ERROR};
  // Creating an array with every square type possible other then lightebulb
  square array_error[19] = {
    S_BLACK | F_ERROR,S_BLACK0 | F_ERROR,S_BLACK1 | F_ERROR,S_BLACK2 | F_ERROR,S_BLACK3 | F_ERROR,S_BLACK4 | F_ERROR,S_BLACKU | F_ERROR,
        S_BLANK, S_BLACK, S_MARK,S_MARK|F_LIGHTED, S_BLANK | F_LIGHTED, S_BLACK1,S_MARK | F_LIGHTED ,S_BLACK2,S_BLACKU,S_BLACK0,S_BLACK3,S_BLACK4
        };
  //Creating a new_game to test
  game game_test = game_new_empty();

  for (int height = 0; height < DEFAULT_SIZE; height++)
  {
    for (int width = 0; width < DEFAULT_SIZE; width++)
    {
      for (int i = 0; i<19;i++){
                game_set_square(game_test,height,width,array_error[i]);
                ASSERT(!game_is_lightbulb(game_test,height,width));
            }
            for (int j = 0; j<2;j++){
                game_set_square(game_test,height,width,lightbulb_array[j]);
                ASSERT(game_is_lightbulb(game_test,height,width)); 
            }
    }
  }
  return true;
}

/* ********** TEST game_is_lighted ********** */

bool test_game_is_lighted()
{
  // Creating an array with only lighted square
  square lighted_array[4] = {S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED | F_ERROR ,S_MARK | F_LIGHTED,S_LIGHTBULB|F_LIGHTED};

  // Creating an array with every square type possible other then lighted
  square array_error[17] = {
      S_BLACK | F_ERROR,S_BLACK0 | F_ERROR,S_BLACK1 | F_ERROR,S_BLACK2 | F_ERROR,S_BLACK3 | F_ERROR,S_BLACK4 | F_ERROR,S_BLACKU | F_ERROR,
       S_BLANK, S_BLACK, S_MARK, S_BLACK1,S_BLACK2,S_BLACKU,S_BLACK0,S_BLACK3,S_BLACK4,S_LIGHTBULB};
  //Creating a new_game to test
  game game_test = game_new_empty();

  for (int height = 0; height < DEFAULT_SIZE; height++)
  {
    for (int width = 0; width < DEFAULT_SIZE; width++)
    {
      for (int i = 0; i<17;i++){
                game_set_square(game_test,height,width,array_error[i]);
                ASSERT(!game_is_lighted(game_test,height,width));
            }
            for (int j = 0; j<4;j++){
                game_set_square(game_test,height,width,lighted_array[j]);
                ASSERT(game_is_lighted(game_test,height,width)); 
            }
    }
  }
  return true;
}

/* ********** TEST game_has_error ********** */

bool test_game_has_error()
{
  // Creating an array with only squares with errors
  square array_of_errors[6] = {S_LIGHTBULB | F_LIGHTED | F_ERROR,S_BLACK0 | F_ERROR,S_BLACK2 | F_ERROR,S_BLACK3 | F_ERROR,S_BLACK3 | F_ERROR,S_BLACK | F_ERROR};

  // Creating an array with squares with no errors
  square array_no_errors[13] = {
      S_BLANK ,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,S_LIGHTBULB,S_MARK,S_BLANK | F_LIGHTED,S_MARK | F_LIGHTED ,S_BLANK};
  //Creating a new_game to test
  game game_test = game_new_empty();

  for (int height = 0; height < DEFAULT_SIZE; height++)
  {
    for (int width = 0; width < DEFAULT_SIZE; width++)
    {
      for (int i = 0; i<13;i++){
                game_set_square(game_test,height,width,array_no_errors[i]);
                ASSERT(!game_has_error(game_test,height,width));
            }
            for (int j = 0; j<6;j++){
                game_set_square(game_test,height,width,array_of_errors[j]);
                ASSERT(game_has_error(game_test,height,width)); 
            }
    }
  }
  return true;
}

/* ********** TEST game_get_flags ********** */

bool test_game_get_flags()
{
  // Creating a new game 
  game game_test = game_new_empty();
  // Creating an array with every square
  square array_all_square[19]={
        S_BLANK ,S_BLACK,S_BLACK0,S_BLACK1,S_BLACK2,S_BLACK3,S_BLACK4,S_BLACKU,
        S_LIGHTBULB,S_MARK,S_BLANK | F_LIGHTED,S_LIGHTBULB | F_LIGHTED | F_ERROR ,S_MARK | F_LIGHTED ,
        S_BLACK0 | F_ERROR,S_BLACK1 | F_ERROR,S_BLACK2 | F_ERROR,S_BLACK3 | F_ERROR,S_BLACK4 | F_ERROR,S_BLACK | F_ERROR
    };
  // Creating an array with every flag
  square array_all_flags[19]={S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,S_BLANK,
  S_BLANK,S_BLANK,F_LIGHTED, F_LIGHTED | F_ERROR ,F_LIGHTED ,
         F_ERROR, F_ERROR, F_ERROR, F_ERROR, F_ERROR, F_ERROR};
  // Asserting that we can get every flag square type in our new game 
  for (int height = 0; height < DEFAULT_SIZE; height++){
        for (int width = 0; width < DEFAULT_SIZE;width++){
            for (int z = 0; z < 19;z++){
            game_set_square(game_test,width,height,array_all_square[z]);
            ASSERT(game_get_flags(game_test,width,height) == array_all_flags[z]); 
            }
        }
    }
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

  if (strcmp("game_print", argv[1]) == 0)
    ok = test_game_print();
  else if (strcmp("game_default", argv[1]) == 0)
    ok = test_game_default();
  else if (strcmp("game_default_solution", argv[1]) == 0)
    ok = test_game_default_solution();
  else if (strcmp("game_delete", argv[1]) == 0)
    ok = test_game_delete();
  else if (strcmp("game_is_blank", argv[1]) == 0)
    ok = test_game_is_blank();
  else if (strcmp("game_is_lightbulb", argv[1]) == 0)
    ok = test_game_is_lightbulb();
  else if (strcmp("game_is_lighted", argv[1]) == 0)
    ok = test_game_is_lighted();
  else if (strcmp("game_has_error", argv[1]) == 0)
    ok = test_game_has_error();
  else if (strcmp("game_get_flags", argv[1]) == 0)
    ok = test_game_get_flags();
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
