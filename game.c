#include "game.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_ext.h"

struct game_s {
  uint height;
  uint width;
  bool wrapping;
  square **cell;
};

typedef struct game_s gameStruct;

game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping) {
  // Validate parameters
  assert(nb_rows >= 0);
  assert(nb_cols >= 0);

  // Allocate memory the new game
  game newGame = (game)malloc(sizeof(gameStruct));
  assert(newGame != NULL);

  // Initialize variables of newgame
  newGame->height = nb_rows;
  newGame->width = nb_cols;
  newGame->wrapping = wrapping;
  newGame->cell = (square **)malloc(newGame->height * sizeof(square *));
  assert(newGame->cell != NULL);

  // Allocte memory to the cells of newgame
  for (int i = 0; i < newGame->width; i++) {
    newGame->cell[i] = (square *)calloc(newGame->width, sizeof(square));
    assert(newGame->cell[i] != NULL);
  }

  // Add values to the matrice of newgame
  for (uint row = 0; row < newGame->height; row++) {
    for (uint column = 0; column < newGame->width; column++) {
      newGame->cell[row][column] = S_BLANK;
    }
  }

  return newGame;
}

game game_new_ext(uint nb_rows, uint nb_cols, square *squares, bool wrapping) {
  // Validate parameters
  assert(squares != NULL);
  assert(nb_rows >= 0);
  assert(nb_cols >= 0);

  game newGame = game_new_empty_ext(nb_rows, nb_cols, wrapping);

  // Add values to the matrice of newgame
  int j = 0;
  for (uint row = 0; row < newGame->height; row++) {
    for (uint column = 0; column < newGame->width; column++) {
      newGame->cell[row][column] = squares[j];
      j = j + 1;
    }
  }

  return newGame;
}

game game_new(square *squares) {
  // Validate parameters
  assert(squares != NULL);
  return game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, squares, false);
}

game game_new_empty(void) {
  // Create a new game with empty squares
  return game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false);
}

game game_copy(cgame g) {
  // Validate parameters
  assert(g != NULL);

  // Create a new game
  game newGame = game_new_empty();

  // Add values to new game
  for (uint row = 0; row < g->height; row++)
    for (uint column = 0; column < g->width; column++)
      game_set_square(newGame, row, column, game_get_square(g, row, column));

  return newGame;
}

bool game_equal(cgame g1, cgame g2) {
  // Validate parameters
  assert(g1 != NULL);
  assert(g2 != NULL);

  // Check if dimensions are equal
  if (g1->height != g2->height || g1->width != g2->width) return false;

  // Check if values are equal
  for (uint row = 0; row < g1->height; row++)
    for (uint column = 0; column < g2->width; column++)
      if (game_get_square(g1, row, column) != game_get_square(g2, row, column))
        return false;

  return true;
}

void game_delete(game g) {
  // free game squares and game memory
  if (g->cell != NULL) {
    for (int i = 0; i < g->height; i++) {
      if (g->cell[i] != NULL) {
        free(g->cell[i]);
        g->cell[i] = NULL;
      }
    }
    free(g->cell);
    g->cell = NULL;
  }

  free(g);
  g = NULL;
}

uint game_nb_rows(cgame g) {
  // Validate parameters
  assert(g != NULL);

  return g->width;
}

uint game_nb_cols(cgame g) {
  // Validate parameters
  assert(g != NULL);

  return g->height;
}

bool game_is_wrapping(cgame g) {
  // Validate parameters
  assert(g != NULL);

  return g->wrapping;
}

void game_set_square(game g, uint i, uint j, square s) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);  // check row parameter
  assert(j < g->width && j >= 0);   // check column parameter

  g->cell[i][j] = s;
}

square game_get_square(cgame g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);  // check row parameter
  assert(j < g->width && j >= 0);   // check column parameter

  return g->cell[i][j];
}

square game_get_state(cgame g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);  // check row parameter
  assert(j < g->width && j >= 0);   // check column parameter

  return g->cell[i][j] & S_MASK;
}

square game_get_flags(cgame g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);  // check row parameter
  assert(j < g->width && j >= 0);   // check column parameter

  return g->cell[i][j] & F_MASK;
}

bool game_is_blank(cgame g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);  // check row parameter
  assert(j < g->width && j >= 0);   // check column parameter

  return game_get_state(g, i, j) == S_BLANK;
}

bool game_is_lightbulb(cgame g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);  // check row parameter
  assert(j < g->width && j >= 0);   // check column parameter

  return game_get_state(g, i, j) == S_LIGHTBULB;
}

int game_get_black_number(cgame g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);  // check row parameter
  assert(j < g->width && j >= 0);   // check column parameter

  square state = game_get_state(g, i, j);

  switch (state) {
    case S_BLACKU:
      return -1;
    case S_BLACK0:
      return 0;
    case S_BLACK1:
      return 1;
    case S_BLACK2:
      return 2;
    case S_BLACK3:
      return 3;
    case S_BLACK4:
      return 4;
    default:
      return 0;
  }
}

bool game_is_black(cgame g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);  // check row parameter
  assert(j < g->width && j >= 0);   // check column parameter

  return game_get_state(g, i, j) & S_BLACK;
}

bool game_is_marked(cgame g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);  // check row parameter
  assert(j < g->width && j >= 0);   // check column parameter

  return game_get_state(g, i, j) == S_MARK;
}

bool game_is_lighted(cgame g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);  // check row parameter
  assert(j < g->width && j >= 0);   // check column parameter

  return game_get_flags(g, i, j) & F_LIGHTED;
}

bool game_has_error(cgame g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);  // check row parameter
  assert(j < g->width && j >= 0);   // check column parameter

  return game_get_flags(g, i, j) & F_ERROR;
}

bool game_check_move(cgame g, uint i, uint j, square s) {
  // Validate parameters
  assert(g != NULL);

  if (i >= g->height || i < 0)  // check row parameter
    return false;
  if (j >= g->width || j < 0)  // check column parameter
    return false;

  // Check that the square is not black (is a lightbulb ,blank or mark) and it
  // doesn't have a flag
  if (s & S_BLACK || s & F_MASK) return false;

  // Check the square is not black
  if (game_is_black(g, i, j)) return false;

  return true;
}

void game_play_move(game g, uint i, uint j, square s) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);
  assert(j < g->width && i >= 0);
  assert(s == S_BLANK || s == S_LIGHTBULB || s == S_MARK);

  game_set_square(g, i, j, s);
  game_update_flags(g);
}

// Applies the effect of the lightbulb on the current square
// Return if light should stop or not
bool apply_effect_of_lightbulb_on_square(game g, uint i, uint j) {
  // light up blank or marked flags
  if (game_is_blank(g, i, j) || game_is_marked(g, i, j)) {
    game_set_square(g, i, j, (game_get_state(g, i, j) | F_LIGHTED));
    return false;
  } else if (game_is_lightbulb(g, i,
                               j)) {  // lightbulbs cause an error
    game_set_square(g, i, j, (game_get_state(g, i, j) | F_LIGHTED | F_ERROR));
    return true;
  } else  // walls stop the light
    return true;
}

void update_lightbulb_flags(game g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);
  assert(j < g->width && i >= 0);

  // Update the flags to the right of the lightbulb until we reach either
  // a wall or another lightbulb
  for (int right = j + 1; right < g->width; right++) {
    if (apply_effect_of_lightbulb_on_square(g, i, right)) break;
  }

  // Update the flags to the left of the lightbulb
  for (int left = j - 1; left >= 0; left--) {
    if (apply_effect_of_lightbulb_on_square(g, i, left)) break;
  }

  // Update the flags above the lightbulb
  for (int up = i - 1; up >= 0; up--) {
    if (apply_effect_of_lightbulb_on_square(g, up, j)) break;
  }

  // Update the flags below the lightbulb
  for (int down = i + 1; down < g->height; down++) {
    if (apply_effect_of_lightbulb_on_square(g, down, j)) break;
  }
}

bool has_intersecting_lightbulb(game g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);
  assert(j < g->width && i >= 0);

  // Iterate the squares to the right of the lightbulb until we reach either
  // a wall or another lightbulb
  for (int right = j + 1; right < g->width; right++) {
    if (game_is_lightbulb(g, i, right))
      return true;
    else if (game_is_black(g, i, right))
      break;
  }

  // Iterate the squares to the left of the lightbulb
  for (int left = j - 1; left >= 0; left--) {
    if (game_is_lightbulb(g, i, left))
      return true;
    else if (game_is_black(g, i, left))
      break;
  }

  // Iterate the squares above the lightbulb
  for (int up = i - 1; up >= 0; up--) {
    if (game_is_lightbulb(g, up, j))
      return true;
    else if (game_is_black(g, up, j))
      break;
  }

  // Iterate the squares below the lightbulb
  for (int down = i + 1; down < g->height; down++) {
    if (game_is_lightbulb(g, down, j))
      return true;
    else if (game_is_black(g, down, j))
      break;
  }

  return false;
}

void update_wall_flags(game g, uint i, uint j) {
  // Validate parameters
  assert(g != NULL);
  assert(i < g->height && i >= 0);
  assert(j < g->width && i >= 0);

  // Get the maximum number of lightbulbs the wall can accept
  int wallLimit = game_get_black_number(g, i, j);
  // If there is a limit verify it
  if (wallLimit != -1) {
    // Find the number of ajacent lightbulbs
    int noAjacentLightbulbs = 0;
    if (i + 1 < g->height && game_is_lightbulb(g, i + 1, j))
      noAjacentLightbulbs++;
    if (j + 1 < g->width && game_is_lightbulb(g, i, j + 1))
      noAjacentLightbulbs++;
    if (j != 0 && game_is_lightbulb(g, i, j - 1)) noAjacentLightbulbs++;
    if (i != 0 && game_is_lightbulb(g, i - 1, j)) noAjacentLightbulbs++;

    if (noAjacentLightbulbs > wallLimit)
      game_set_square(g, i, j, (game_get_state(g, i, j) | F_ERROR));
    else {
      // If the ajacent lightbulbs havent caused an error
      // check if other (non-ajacent) lightbulbs cause an error
      int noAvailableValidLightbulbSpots = 4;

      // Check if the square to the right of the wall can accept a
      // lightbulb, it cant if it is on an edge or black
      if (j + 1 >= g->width || game_is_black(g, i, j + 1))
        noAvailableValidLightbulbSpots--;
      else  // check if a lightbulb intersects
          if (has_intersecting_lightbulb(g, i, j + 1))
        noAvailableValidLightbulbSpots--;

      // Check if the square to the left of the wall can accept a
      // lightbulb,
      if (j == 0 || game_is_black(g, i, j - 1))
        noAvailableValidLightbulbSpots--;
      else  // check if a lightbulb is on the row to the left
          if (has_intersecting_lightbulb(g, i, j - 1))
        noAvailableValidLightbulbSpots--;

      // Check if the square above the wall can accept a lightbulb,
      if (i == 0 || game_is_black(g, i - 1, j))
        noAvailableValidLightbulbSpots--;
      else  // check if a lightbulb is on the column above
          if (has_intersecting_lightbulb(g, i - 1, j))
        noAvailableValidLightbulbSpots--;

      // Check if the square below the wall can accept a lightbulb,
      if (i + 1 >= g->height || game_is_black(g, i + 1, j))
        noAvailableValidLightbulbSpots--;
      else  // check if a lightbulb is on the column below
          if (has_intersecting_lightbulb(g, i + 1, j))
        noAvailableValidLightbulbSpots--;

      // If the number of lightbulbs that can be placed will be less
      // the required amount the wall is flagged as in error
      if (noAjacentLightbulbs + noAvailableValidLightbulbSpots < wallLimit)
        game_set_square(g, i, j, (game_get_state(g, i, j) | F_ERROR));
    }
  }
}

void remove_all_flags(game g) {
  // Validate parameters
  assert(g != NULL);

  // Set square value of each square to state value
  for (uint row = 0; row < g->height; row++) {
    for (uint column = 0; column < g->width; column++) {
      game_set_square(g, row, column, game_get_state(g, row, column));
    }
  }
}

void game_update_flags(game g) {
  // Validate parameters
  assert(g != NULL);

  remove_all_flags(g);

  // Check each square is valid
  for (uint row = 0; row < g->height; row++) {
    for (uint column = 0; column < g->width; column++) {
      if (game_is_lightbulb(g, row, column)) {
        // Add light to lightbulb
        game_set_square(g, row, column,
                        (game_get_square(g, row, column) | F_LIGHTED));
        update_lightbulb_flags(g, row, column);
      } else if (game_is_black(g, row, column)) {
        update_wall_flags(g, row, column);
      }
    }
  }
}

bool game_is_over(cgame g) {
  // Validate parameters
  assert(g != NULL);

  // Check each square is valid
  for (uint row = 0; row < g->height; row++) {
    for (uint column = 0; column < g->width; column++) {
      // Get the state and the flags
      square state = game_get_state(g, row, column);
      square flags = game_get_flags(g, row, column);

      // Check the flags depending on the state
      switch (state) {
        case S_BLANK:
        case S_MARK:
          if (flags != F_LIGHTED) return false;
          break;
        case S_LIGHTBULB:
          if (flags & F_ERROR || !(flags & F_LIGHTED)) return false;
          break;
        case S_BLACK0:
        case S_BLACK1:
        case S_BLACK2:
        case S_BLACK3:
        case S_BLACK4:
        case S_BLACKU:
          if (flags & F_ERROR) return false;
          break;
        default:
          return false;
      }
    }
  }

  return true;
}

void game_restart(game g) {
  // Validate parameters
  assert(g != NULL);

  for (uint row = 0; row < g->height; row++) {
    for (uint column = 0; column < g->width; column++) {
      if (game_is_black(g, row, column)) {
        if (game_has_error(g, row, column)) {
          game_set_square(g, row, column, game_get_state(g, row, column));
        }
      } else {
        game_set_square(g, row, column, S_BLANK);
      }
    }
  }
}
