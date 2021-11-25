#include "game.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct game_s {
    uint height;
    uint width;
    square **cell;
};

game game_new(square *squares) {
    // Validate parameters
    assert(squares != NULL);

    // Allocate memory the new game
    game newGame = (game)malloc(sizeof(game));
    assert(newGame != NULL);

    // Initialize variables of newgame
    newGame->height = DEFAULT_SIZE;
    newGame->width = DEFAULT_SIZE;
    newGame->cell = (square **)malloc(newGame->height * sizeof(square *));
    assert(newGame->cell != NULL);

    // Allocte memory to the cells of newgame
    for (int i = 0; i < newGame->width; i++) {
        newGame->cell[i] = (square *)calloc(newGame->width, sizeof(square));
        assert(newGame->cell[i] != NULL);
    }

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

game game_new_empty(void) {
    // Creates an array of empty squares
    square arrayGameEmpty[DEFAULT_SIZE * DEFAULT_SIZE] = {
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK,
        S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK, S_BLANK};

    // Create a new game with empty squares
    return game_new(arrayGameEmpty);
}

game game_copy(cgame g) { return NULL; }

bool game_equal(cgame g1, cgame g2) { return false; }

void game_delete(game g) {
    // Validate parameters
    if (g == NULL) {
        return;
    }

    // free game squares and game memory
    for (int i = 0; i < g->height; i++) {
        if (g->cell[i] != NULL) {
            free(g->cell[i]);
            g->cell[i] = NULL;
        }    
    }
    
    free(g);
    g=NULL;
}

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

    return g->cell[i][j] & S_MASK;
}

square game_get_flags(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

    return g->cell[i][j] & F_MASK;
}

bool game_is_blank(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

    return game_get_state(g, i, j) == S_BLANK;
}

bool game_is_lightbulb(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

    return game_get_state(g, i, j) == S_LIGHTBULB;
}

int game_get_black_number(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

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
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

    return game_get_state(g, i, j) & S_BLACK;
}

bool game_is_marked(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

    return game_get_state(g, i, j) == S_MARK;
}

bool game_is_lighted(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

    return game_get_flags(g, i, j) & F_LIGHTED;
}

bool game_has_error(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g != NULL);
    assert(i < g->height && i >= 0); // check row parameter
    assert(j < g->width && j >= 0);  // check column parameter

    return game_get_flags(g, i, j) & F_ERROR;
}

bool game_check_move(cgame g, uint i, uint j, square s) { return false; }

void game_play_move(game g, uint i, uint j, square s) {}

void game_update_flags(game g) {}

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
                if (flags != F_LIGHTED)
                    return false;
                break;
            case S_LIGHTBULB:
                if (flags & F_ERROR || !(flags & F_LIGHTED))
                    return false;
                break;
            case S_BLACK0:
            case S_BLACK1:
            case S_BLACK2:
            case S_BLACK3:
            case S_BLACK4:
            case S_BLACKU:
                if (flags & F_ERROR)
                    return false;
                break;
            default:
                return false;
            }
        }
    }

    return true;
}

void game_restart(game g) {}
