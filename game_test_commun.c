#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"

#define SIZE_ALL_VALUES 20

/* ********** ASSERT ********** */

#define ASSERT(expr)                                                          \
  do {                                                                        \
    if ((expr) == 0) {                                                        \
      fprintf(stderr, "[%s:%d] Assertion '%s' failed!\n", __FILE__, __LINE__, \
              #expr);                                                         \
      abort();                                                                \
    }                                                                         \
  } while (0)

/* ************************************************************************** */

// default game with some moves that cause an error
game game_default_other() {
  square squares[] = {
      (S_LIGHTBULB | F_LIGHTED | F_ERROR),
      F_LIGHTED,
      S_BLACK1,
      S_BLANK,
      S_BLANK,
      S_BLANK,
      S_BLANK, /* row 0 */
      F_LIGHTED,
      S_BLANK,
      S_BLACK2,
      S_BLANK,
      S_BLANK,
      S_BLANK,
      S_BLANK, /* row 1 */
      F_LIGHTED,
      S_BLANK,
      S_BLANK,
      S_BLANK,
      S_BLANK,
      S_BLACKU,
      (S_BLACK2 | F_ERROR), /* row 2 */
      (S_LIGHTBULB | F_LIGHTED | F_ERROR),
      F_LIGHTED,
      F_LIGHTED,
      F_LIGHTED,
      F_LIGHTED,
      F_LIGHTED,
      F_LIGHTED, /* row 3 */
      S_BLACK1,
      S_BLACKU,
      S_BLANK,
      S_BLANK,
      S_BLANK,
      S_BLANK,
      S_BLANK, /* row 4 */
      S_BLANK,
      S_BLANK,
      S_BLANK,
      S_BLANK,
      S_BLACK2,
      S_BLANK,
      S_BLANK, /* row 5 */
      S_BLANK,
      S_BLANK,
      S_BLANK,
      S_BLANK,
      S_BLACKU,
      S_BLANK,
      S_MARK, /* row 6 */
  };
  return game_new(squares);
}

/* ********** TEST COMMUN ********** */

bool check_game(square *liste, game game_test) {
  for (uint y = 0; y < DEFAULT_SIZE; y++) {
    for (uint x = 0; x < DEFAULT_SIZE; x++) {
      square carre = game_get_square(game_test, y, x);
      if (liste[x + DEFAULT_SIZE * y] != carre) {
        return false;
      }
    }
  }
  return true;
}

square *create_array_all_values() {
  square *array_all_values =
      (square *)malloc(sizeof(square) * DEFAULT_SIZE * DEFAULT_SIZE);

  if (array_all_values == NULL) {
    fprintf(stderr, "NULL POINTER");
    exit(EXIT_FAILURE);
  }
  square array[20] = {S_BLANK,
                      S_BLACK,
                      S_BLACK0,
                      S_BLACK1,
                      S_BLACK2,
                      S_BLACK3,
                      S_BLACK4,
                      S_BLACKU,
                      S_LIGHTBULB,
                      S_MARK,
                      S_BLANK | F_LIGHTED,
                      S_LIGHTBULB | F_LIGHTED,
                      S_LIGHTBULB | F_LIGHTED | F_ERROR,
                      S_MARK | F_LIGHTED,
                      S_BLACK0 | F_ERROR,
                      S_BLACK1 | F_ERROR,
                      S_BLACK2 | F_ERROR,
                      S_BLACK3 | F_ERROR,
                      S_BLACK4 | F_ERROR,
                      S_BLACK | F_ERROR};
  for (int i = 0; i < DEFAULT_SIZE * DEFAULT_SIZE; i++) {
    array_all_values[i] = array[i];
  }
  return array_all_values;
}
