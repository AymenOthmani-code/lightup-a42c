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

game game_copy(cgame g) {
    // Validate parameters
    assert(g != NULL);

    // Create a new game
    game newGame = game_new_empty();

    // Add values to new game
    for (uint row = 0; row < g->height; row++)
        for (uint column = 0; column < g->width; column++)
            game_set_square(newGame, row, column,
                            game_get_square(g, row, column));

    return newGame;
}

bool game_equal(cgame g1, cgame g2) {
    // Validate parameters
    assert(g1 != NULL);
    assert(g2 != NULL);

    // Check if dimensions are equal
    if (g1->height != g2->height || g1->width != g2->width)
        return false;

    // Check if values are equal
    for (uint row = 0; row < g1->height; row++)
        for (uint column = 0; column < g2->width; column++)
            if (game_get_square(g1, row, column) !=
                game_get_square(g2, row, column))
                return false;

    return true;
}

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

void game_play_move(game g, uint i, uint j, square s) {}

void game_update_flags(game g) {}

bool game_is_over(cgame g) { return false; }

void game_restart(game g) {}
