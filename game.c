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

void game_set_square(game g, uint i, uint j, square s) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

    g->cell[i][j] = s;
}

square game_get_square(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

    return g->cell[i][j];
}

square game_get_state(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

    return g->cell[i][j];
}

square game_get_flags(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

    return g->cell[i][j];
}

bool game_is_blank(cgame g, uint i, uint j) { return false; }

bool game_is_lightbulb(cgame g, uint i, uint j) { return false; }

bool game_is_black(cgame g, uint i, uint j) { return false; }

int game_get_black_number(cgame g, uint i, uint j) {
    // Parameters Validations
    assert(g != NULL);
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

    square state = game_get_state(g, i, j);

    switch (state) {
    case S_BLACKU:
        return -1;
    case S_BLACK:
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

bool game_is_marked(cgame g, uint i, uint j) { return false; }

bool game_is_lighted(cgame g, uint i, uint j) { return false; }

bool game_has_error(cgame g, uint i, uint j) { return false; }

bool game_check_move(cgame g, uint i, uint j, square s) { return false; }

void game_play_move(game g, uint i, uint j, square s) {}

void game_update_flags(game g) {}

bool game_is_over(cgame g) { return false; }

void game_restart(game g) {}
