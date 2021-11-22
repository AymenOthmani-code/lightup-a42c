#include "game_aux.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct game_s {
    uint height;
    uint width;
    square **cell;
};

game game_new(square *squares) { return NULL; }

game game_new_empty(void) { return NULL; }

game game_copy(cgame g) { return NULL; }

bool game_equal(cgame g1, cgame g2) { return false; }

void game_delete(game g) {}

void game_set_square(game g, uint i, uint j, square s) {}

square game_get_square(cgame g, uint i, uint j) {
    // Validation
    assert(g != NULL);
    assert(i < g->height); // check row parameter
    assert(j < g->width);  // check column parameter

    return g->cell[i][j];
}

square game_get_state(cgame g, uint i, uint j) { return S_BLANK; }

square game_get_flags(cgame g, uint i, uint j) { return S_BLANK; }

bool game_is_blank(cgame g, uint i, uint j) { return false; }

bool game_is_lightbulb(cgame g, uint i, uint j) { return false; }

bool game_is_black(cgame g, uint i, uint j) { return false; }

int game_get_black_number(cgame g, uint i, uint j) { return false; }

bool game_is_marked(cgame g, uint i, uint j) { return false; }

bool game_is_lighted(cgame g, uint i, uint j) { return false; }

bool game_has_error(cgame g, uint i, uint j) { return false; }

bool game_check_move(cgame g, uint i, uint j, square s) { return false; }

void game_play_move(game g, uint i, uint j, square s) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0);
    assert(j < g->width && i >= 0);
    assert(s == S_BLANK || s == S_LIGHTBULB || s == S_MARK);

    game_set_square(g, i, j, s);
    game_update_flags(g);
}

void update_lightbulb_flags(game g, uint i, uint j) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0);
    assert(j < g->width && i >= 0);

    // Update the flags to the right of the lightbulb until we reach either a
    // wall or another lightbulb
    for (int right = j + 1; right < g->width; right++) {
        // light up blank or marked flags
        if (game_is_blank(g, i, right) || game_is_marked(g, i, right)) {
            game_set_square(g, i, right,
                            (game_get_state(g, i, right) | F_LIGHTED));
        } else if (game_is_lightbulb(g, i,
                                     right)) { // lightbulbs cause an error
            game_set_square(g, i, j,
                            (game_get_state(g, i, j) | F_LIGHTED | F_ERROR));
            break;
        } else // walls stop the light
            break;
    }

    // Update the flags to the left of the lightbulb until we reach either a
    // wall or another lightbulb
    for (int left = j - 1; left >= 0; left--) {
        // light up blank or marked flags
        if (game_is_blank(g, i, left) || game_is_marked(g, i, left)) {
            game_set_square(g, i, left,
                            (game_get_state(g, i, left) | F_LIGHTED));
        } else if (game_is_lightbulb(g, i, left)) { // lightbulbs cause an error
            game_set_square(g, i, j,
                            (game_get_state(g, i, j) | F_LIGHTED | F_ERROR));
            break;
        } else // walls stop the light
            break;
    }

    // Update the flags above the lightbulb until we reach either a
    // wall or another lightbulb
    for (int up = i - 1; up >= 0; up--) {
        // light up blank or marked flags
        if (game_is_blank(g, up, j) || game_is_marked(g, up, j)) {
            game_set_square(g, up, j, (game_get_state(g, up, j) | F_LIGHTED));
        } else if (game_is_lightbulb(g, up, j)) { // lightbulbs cause an error
            game_set_square(g, i, j,
                            (game_get_state(g, i, j) | F_LIGHTED | F_ERROR));
            break;
        } else // walls stop the light
            break;
    }

    // Update the flags below the lightbulb until we reach either a
    // wall or another lightbulb
    for (int down = i + 1; down < g->height; down++) {
        // light up blank or marked flags
        if (game_is_blank(g, down, j) || game_is_marked(g, down, j)) {
            game_set_square(g, down, j,
                            (game_get_state(g, down, j) | F_LIGHTED));
        } else if (game_is_lightbulb(g, down, j)) { // lightbulbs cause an error
            game_set_square(g, i, j,
                            (game_get_state(g, i, j) | F_LIGHTED | F_ERROR));
            break;
        } else // walls stop the light
            break;
    }
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
        if (j != 0 && game_is_lightbulb(g, i, j - 1))
            noAjacentLightbulbs++;
        if (i != 0 && game_is_lightbulb(g, i - 1, j))
            noAjacentLightbulbs++;

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
            else // check if a lightbulb is on the row to the right
                for (uint right = j + 1; right < g->width; right++) {
                    if (game_is_black(g, i, right)) {
                        break;
                    } else if (game_is_lightbulb(g, i, right)) {
                        noAvailableValidLightbulbSpots--;
                        break;
                    }
                }

            // Check if the square to the left of the wall can accept a
            // lightbulb,
            if (j == 0 || game_is_black(g, i, j - 1))
                noAvailableValidLightbulbSpots--;
            else // check if a lightbulb is on the row to the left
                for (int left = j - 1; left >= 0; left--) {
                    if (game_is_black(g, i, left)) {
                        break;
                    } else if (game_is_lightbulb(g, i, left)) {
                        noAvailableValidLightbulbSpots--;
                        break;
                    }
                }

            // Check if the square above the wall can accept a lightbulb,
            if (i == 0 || game_is_black(g, i - 1, j))
                noAvailableValidLightbulbSpots--;
            else // check if a lightbulb is on the column above
                for (int up = i - 1; up >= 0; up--) {
                    if (game_is_black(g, up, j)) {
                        break;
                    } else if (game_is_lightbulb(g, up, j)) {
                        noAvailableValidLightbulbSpots--;
                        break;
                    }
                }

            // Check if the square below the wall can accept a lightbulb,
            if (i + 1 >= g->height || game_is_black(g, i + 1, j))
                noAvailableValidLightbulbSpots--;
            else // check if a lightbulb is on the column below
                for (uint down = i + 1; down < g->height; down++) {
                    if (game_is_black(g, down, j)) {
                        break;
                    } else if (game_is_lightbulb(g, down, j)) {
                        noAvailableValidLightbulbSpots--;
                        break;
                    }
                }

            // If the number of lightbulbs that can be placed will be less the
            // required amount the wall is flagged as in error
            if (noAjacentLightbulbs + noAvailableValidLightbulbSpots <
                wallLimit)
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
                                (game_get_state(g, row, column) | F_LIGHTED));
                update_lightbulb_flags(g, row, column);
            } else if (game_is_black(g, row, column)) {
                update_wall_flags(g, row, column);
            }
        }
    }
}

bool game_is_over(cgame g) { return false; }

void game_restart(game g) {}
