#include <stdlib.h>
#include <stdio.h>
#include "game_aux.h"

struct game_s
{
    square **cell;
};

game game_new(square *squares)
{
    return NULL;
}

game game_new_empty(void)
{
    return NULL;
}

game game_copy(cgame g)
{
    return NULL;
}

bool game_equal(cgame g1, cgame g2)
{
    return false;
}

void game_delete(game g) {}

void game_set_square(game g, uint i, uint j, square s) {}

square game_get_square(cgame g, uint i, uint j)
{
    return S_BLANK;
}

square game_get_state(cgame g, uint i, uint j)
{
    return S_BLANK;
}

square game_get_flags(cgame g, uint i, uint j)
{
    return S_BLANK;
}

bool game_is_blank(cgame g, uint i, uint j)
{
    return false;
}

bool game_is_lightbulb(cgame g, uint i, uint j)
{
    return false;
}

bool game_is_black(cgame g, uint i, uint j)
{
    return false;
}

int game_get_black_number(cgame g, uint i, uint j)
{
    return false;
}

bool game_is_marked(cgame g, uint i, uint j)
{
    return false;
}

bool game_is_lighted(cgame g, uint i, uint j)
{
    return false;
}

bool game_has_error(cgame g, uint i, uint j)
{
    return false;
}

bool game_check_move(cgame g, uint i, uint j, square s)
{
    return false;
}

void game_play_move(game g, uint i, uint j, square s) {}

void game_update_flags(game g) {}

bool game_is_over(cgame g)
{
    return false;
}

void game_restart(game g) {}