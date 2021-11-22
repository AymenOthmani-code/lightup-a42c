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
    // Validation
    assert(g != NULL);
    assert(i < g->height); // check row parameter
    assert(j < g->width);  // check column parameter
    g->cell[i][j] = s;
}

square game_get_square(cgame g, uint i, uint j) {
    // Validation
    assert(g != NULL);
    assert(i < g->height); // check row parameter
    assert(j < g->width);  // check column parameter

    return g->cell[i][j];
}

square game_get_state(cgame g, uint i, uint j) { return S_BLANK; }

square game_get_flags(cgame g, uint i, uint j) { return S_BLANK; }

bool game_is_blank(cgame g, uint i, uint j) {
    // Validation
    assert(g != NULL);
    assert(i < g->height); // check row parameter
    assert(j < g->width);  // check column parameter

    return game_get_state(g, i, j) == S_BLANK;
}

bool game_is_lightbulb(cgame g, uint i, uint j) {
    // Validation
    assert(g != NULL);
    assert(i < g->height); // check row parameter
    assert(j < g->width);  // check column parameter

    return game_get_state(g, i, j) == S_LIGHTBULB;
}

bool game_is_black(cgame g, uint i, uint j) {
    // Validation
    assert(g != NULL);
    assert(i < g->height); // check row parameter
    assert(j < g->width);  // check column parameter

    return game_get_state(g, i, j) & S_BLACK;
}

int game_get_black_number(cgame g, uint i, uint j) {
    // Validation
    assert(g != NULL);
    assert(i < g->height); // check row parameter
    assert(j < g->width);  // check column parameter

    if (game_get_state(g, i, j) == S_BLACKU) {
        return -1;
    } else if (game_get_state(g, i, j) == S_BLACK0) {
        return 0;
    } else if (game_get_state(g, i, j) == S_BLACK1) {
        return 1;
    } else if (game_get_state(g, i, j) == S_BLACK2) {
        return 2;
    } else if (game_get_state(g, i, j) == S_BLACK3) {
        return 3;
    } else if (game_get_state(g, i, j) == S_BLACK4) {
        return 4;
    } else {
        return 0;
    }
}

bool game_is_marked(cgame g, uint i, uint j) {
    // Validation
    assert(g != NULL);
    assert(i < g->height); // check row parameter
    assert(j < g->width);  // check column parameter

    return game_get_state(g, i, j) == S_MARK;
}

bool game_is_lighted(cgame g, uint i, uint j) {
    // Validation
    assert(g != NULL);
    assert(i < g->height); // check row parameter
    assert(j < g->width);  // check column parameter

    return game_get_flags(g, i, j) == F_LIGHTED;
}

bool game_has_error(cgame g, uint i, uint j) {
    // Validation
    assert(g != NULL);
    assert(i < g->height); // check row parameter
    assert(j < g->width);  // check column parameter
    
    return game_get_flags(g, i, j) == F_ERROR;
}

bool game_check_move(cgame g, uint i, uint j, square s) { return false; }

void game_play_move(game g, uint i, uint j, square s) {}

void game_update_flags(game g) {}

bool game_is_over(cgame g) { return false; }

void game_restart(game g) {}
