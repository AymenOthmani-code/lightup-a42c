#include "game.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_ext.h"
#include "queue.h"

typedef struct game_cell {
    int col;
    int row;
} game_cell;

typedef struct game_line {
    uint size;
    game_cell *line;
} game_line;

typedef struct game_move {
    uint col;
    uint row;
    square previous;
    square current;
} game_move;

struct game_s {
    uint height;
    uint width;
    bool wrapping;
    queue *undo_queue;
    queue *redo_queue;
    square **cell;
};

typedef struct game_s gameStruct;

game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping) {
    // Validate parameters
    assert(nb_rows > 0);
    assert(nb_cols > 0);

    // Allocate memory the new game
    game newGame = (game)malloc(sizeof(gameStruct));
    assert(newGame);

    // Initialize variables of newgame
    newGame->height = nb_rows;
    newGame->width = nb_cols;
    newGame->wrapping = wrapping;

    newGame->undo_queue = queue_new();
    newGame->redo_queue = queue_new();

    newGame->cell = (square **)malloc(nb_rows * sizeof(square *));
    assert(newGame->cell != NULL);

    // Allocte memory to the cells of newgame
    for (int i = 0; i < nb_rows; i++) {
        newGame->cell[i] = (square *)calloc(nb_cols, sizeof(square));
        assert(newGame->cell[i] != NULL);
    }

    // Add values to the matrice of newgame
    for (uint row = 0; row < nb_rows; row++) {
        for (uint column = 0; column < nb_cols; column++) {
            newGame->cell[row][column] = S_BLANK;
        }
    }

    return newGame;
}

game game_new_ext(uint nb_rows, uint nb_cols, square *squares, bool wrapping) {
    // Validate parameters
    assert(squares != NULL);
    assert(nb_rows > 0);
    assert(nb_cols > 0);

    game newGame = game_new_empty_ext(nb_rows, nb_cols, wrapping);

    // Add values to the matrice of newgame
    int j = 0;
    for (uint row = 0; row < game_nb_rows(newGame); row++) {
        for (uint column = 0; column < game_nb_cols(newGame); column++) {
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
    assert(g);

    // Create a new game
    game newGame = game_new_empty_ext(game_nb_rows(g), game_nb_cols(g),
                                      game_is_wrapping(g));

    // Add values to new game
    for (uint row = 0; row < game_nb_rows(g); row++)
        for (uint column = 0; column < game_nb_cols(g); column++)
            game_set_square(newGame, row, column,
                            game_get_square(g, row, column));

    return newGame;
}

bool game_equal(cgame g1, cgame g2) {
    // Validate parameters
    assert(g1);
    assert(g2);

    // Check if dimensions are equal
    if (game_nb_rows(g1) != game_nb_rows(g2) ||
        game_nb_cols(g1) != game_nb_cols(g2))
        return false;

    // Check if wrapping is equal
    if (game_is_wrapping(g1) != game_is_wrapping(g2)) return false;

    // Check if values are equal
    for (uint row = 0; row < game_nb_rows(g1); row++)
        for (uint column = 0; column < game_nb_cols(g2); column++)
            if (game_get_square(g1, row, column) !=
                game_get_square(g2, row, column))
                return false;

    return true;
}

void game_delete(game g) {
    if (g) {
        // free game squares and game memory
        if (g->cell != NULL) {
            for (int i = 0; i < game_nb_rows(g); i++) {
                if (g->cell[i] != NULL) {
                    free(g->cell[i]);
                    g->cell[i] = NULL;
                }
            }
            free(g->cell);
            g->cell = NULL;
        }

        if (g->undo_queue != NULL) {
            queue_free_full(g->undo_queue, free);
        }

        if (g->redo_queue != NULL) {
            queue_free_full(g->redo_queue, free);
        }

        free(g);
        g = NULL;
    }
}

uint game_nb_rows(cgame g) {
    // Validate parameters
    assert(g);

    return g->height;
}

uint game_nb_cols(cgame g) {
    // Validate parameters
    assert(g);

    return g->width;
}

bool game_is_wrapping(cgame g) {
    // Validate parameters
    assert(g);

    return g->wrapping;
}

void game_set_square(game g, uint i, uint j, square s) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);  // check row parameter
    assert(j < game_nb_cols(g) && j >= 0);  // check column parameter

    g->cell[i][j] = s;
}

square game_get_square(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);  // check row parameter
    assert(j < game_nb_cols(g) && j >= 0);  // check column parameter

    return g->cell[i][j];
}

square game_get_state(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);  // check row parameter
    assert(j < game_nb_cols(g) && j >= 0);  // check column parameter

    return g->cell[i][j] & S_MASK;
}

square game_get_flags(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);  // check row parameter
    assert(j < game_nb_cols(g) && j >= 0);  // check column parameter

    return g->cell[i][j] & F_MASK;
}

bool game_is_blank(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);  // check row parameter
    assert(j < game_nb_cols(g) && j >= 0);  // check column parameter

    return game_get_state(g, i, j) == S_BLANK;
}

bool game_is_lightbulb(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);  // check row parameter
    assert(j < game_nb_cols(g) && j >= 0);  // check column parameter

    return game_get_state(g, i, j) == S_LIGHTBULB;
}

int game_get_black_number(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);  // check row parameter
    assert(j < game_nb_cols(g) && j >= 0);  // check column parameter

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
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);  // check row parameter
    assert(j < game_nb_cols(g) && j >= 0);  // check column parameter

    return game_get_state(g, i, j) & S_BLACK;
}

bool game_is_marked(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);  // check row parameter
    assert(j < game_nb_cols(g) && j >= 0);  // check column parameter

    return game_get_state(g, i, j) == S_MARK;
}

bool game_is_lighted(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);  // check row parameter
    assert(j < game_nb_cols(g) && j >= 0);  // check column parameter

    return game_get_flags(g, i, j) & F_LIGHTED;
}

bool game_has_error(cgame g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);  // check row parameter
    assert(j < game_nb_cols(g) && j >= 0);  // check column parameter

    return game_get_flags(g, i, j) & F_ERROR;
}

bool game_check_move(cgame g, uint i, uint j, square s) {
    // Validate parameters
    assert(g);

    if (i >= game_nb_rows(g) || i < 0)  // check row parameter
        return false;
    if (j >= game_nb_cols(g) || j < 0)  // check column parameter
        return false;

    // Check that the square is not black (is a lightbulb ,blank or mark) and it
    // doesn't have a flag
    if (s & S_BLACK || s & F_MASK) return false;

    // Check the square is not black
    if (game_is_black(g, i, j)) return false;

    return true;
}

void game_undo(game g) {
    // Validate parameters
    assert(g);

    if (!queue_is_empty(g->undo_queue)) {
        game_move *data = (game_move *)queue_pop_head(g->undo_queue);

        assert(data->current == game_get_state(g, data->row, data->col));

        game_set_square(g, data->row, data->col, data->previous);
        game_update_flags(g);

        queue_push_head(g->redo_queue, data);
    }
}

void game_redo(game g) {
    // Validate parameters
    assert(g);

    if (!queue_is_empty(g->redo_queue)) {
        game_move *data = (game_move *)queue_pop_head(g->redo_queue);
        printf("%d, %d\n", data->previous,
               game_get_state(g, data->row, data->col));
        assert(data->previous == game_get_state(g, data->row, data->col));

        game_set_square(g, data->row, data->col, data->current);
        game_update_flags(g);

        queue_push_head(g->undo_queue, data);
    }
}

void game_play_move(game g, uint i, uint j, square s) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);
    assert(j < game_nb_cols(g) && i >= 0);
    assert(s == S_BLANK || s == S_LIGHTBULB || s == S_MARK);

    game_move *data = (game_move *)malloc(sizeof(game_move));
    assert(data);

    data->col = j;
    data->row = i;
    data->previous = game_get_state(g, i, j);

    game_set_square(g, i, j, s);
    game_update_flags(g);

    data->current = game_get_state(g, i, j);

    queue_push_head(g->undo_queue, data);

    queue_clear_full(g->redo_queue, free);
}

game_cell *get_ajacent_cells(game g, uint i, uint j, uint *size) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);
    assert(j < game_nb_cols(g) && i >= 0);

    // Initialise variables
    uint sizeOfCells = 0;
    game_cell up;
    game_cell right;
    game_cell down;
    game_cell left;
    up.row = -1;
    up.col = -1;
    down.row = -1;
    down.col = -1;
    right.row = -1;
    right.col = -1;
    left.row = -1;
    left.col = -1;

    // Assign the values of up, down, right and left depending on if it is
    // wrapping or not
    if (game_is_wrapping(g)) {
        sizeOfCells = 4;
        if (i + 1 < game_nb_rows(g)) {
            down.col = j;
            down.row = i + 1;
        } else {
            down.col = j;
            down.row = 0;
        }
        if (j + 1 < game_nb_cols(g)) {
            right.col = j + 1;
            right.row = i;
        } else {
            right.col = 0;
            right.row = i;
        }
        if (j != 0) {
            left.col = j - 1;
            left.row = i;
        } else {
            left.col = game_nb_cols(g) - 1;
            left.row = i;
        }
        if (i != 0) {
            up.col = j;
            up.row = i - 1;
        } else {
            up.col = j;
            up.row = game_nb_rows(g) - 1;
        }
    } else {
        if (i + 1 < game_nb_rows(g)) {
            sizeOfCells++;
            down.col = j;
            down.row = i + 1;
        }
        if (j + 1 < game_nb_cols(g)) {
            sizeOfCells++;
            right.col = j + 1;
            right.row = i;
        }
        if (j != 0) {
            sizeOfCells++;
            left.col = j - 1;
            left.row = i;
        }
        if (i != 0) {
            sizeOfCells++;
            up.col = j;
            up.row = i - 1;
        }
    }

    // Allocate memory
    game_cell *cells = (game_cell *)malloc(sizeOfCells * sizeof(game_cell));
    assert(cells);

    // Assign values of the cells
    uint x = 0;
    if (up.col != -1 && x < sizeOfCells) {
        cells[x].col = up.col;
        cells[x].row = up.row;
        x++;
    }
    if (down.col != -1 && x < sizeOfCells) {
        cells[x].col = down.col;
        cells[x].row = down.row;
        x++;
    }
    if (right.col != -1 && x < sizeOfCells) {
        cells[x].col = right.col;
        cells[x].row = right.row;
        x++;
    }
    if (left.col != -1 && x < sizeOfCells) {
        cells[x].col = left.col;
        cells[x].row = left.row;
        x++;
    }

    // Assign the size and return the cells
    *size = sizeOfCells;
    return cells;
}

game_line *get_ajacent_lines(game g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);
    assert(j < game_nb_cols(g) && i >= 0);

    // Allocate memory
    game_line *line = (game_line *)malloc(4 * sizeof(game_line));
    assert(line);

    // Set size of the lines depending on if the game is wrapping or not
    if (game_is_wrapping(g)) {
        line[0].size = game_nb_rows(g) - 1;
        line[1].size = game_nb_cols(g) - 1;
        line[2].size = game_nb_rows(g) - 1;
        line[3].size = game_nb_cols(g) - 1;
    } else {
        line[0].size = i;
        line[3].size = j;
        line[2].size = game_nb_rows(g) - 1 - i;
        line[1].size = game_nb_cols(g) - 1 - j;
    }

    // UP
    line[0].line = (game_cell *)calloc(line[0].size, sizeof(game_cell));
    assert(line[0].line);
    int x = j;
    int y = i - 1;
    for (uint z = 0; z < line[0].size; z++) {
        if (y == -1) y = game_nb_rows(g) - 1;
        line[0].line[z].row = y--;
        line[0].line[z].col = x;
    }

    // RIGHT
    line[1].line = (game_cell *)calloc(line[1].size, sizeof(game_cell));
    assert(line[1].line);
    x = j + 1;
    y = i;
    for (uint z = 0; z < line[1].size; z++) {
        if (x == game_nb_cols(g)) x = 0;
        line[1].line[z].row = y;
        line[1].line[z].col = x++;
    }

    // DOWN
    line[2].line = (game_cell *)calloc(line[2].size, sizeof(game_cell));
    assert(line[2].line);
    x = j;
    y = i + 1;
    for (uint z = 0; z < line[2].size; z++) {
        if (y == game_nb_rows(g)) y = 0;
        line[2].line[z].row = y++;
        line[2].line[z].col = x;
    }

    // LEFT
    line[3].line = (game_cell *)calloc(line[3].size, sizeof(game_cell));
    assert(line[3].line);
    x = j - 1;
    y = i;
    for (uint z = 0; z < line[3].size; z++) {
        if (x == -1) x = game_nb_cols(g) - 1;
        line[3].line[z].row = y;
        line[3].line[z].col = x--;
    }

    return line;
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
        game_set_square(g, i, j,
                        (game_get_state(g, i, j) | F_LIGHTED | F_ERROR));
        return true;
    } else  // walls stop the light
        return true;
}

void update_lightbulb_flags(game g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);
    assert(j < game_nb_cols(g) && i >= 0);

    game_line *line = get_ajacent_lines(g, i, j);

    for (uint x = 0; x < 4; x++) {
        for (uint y = 0; y < line[x].size; y++) {
            if (apply_effect_of_lightbulb_on_square(g, line[x].line[y].row,
                                                    line[x].line[y].col))
                break;
        }
        free(line[x].line);
        line[x].line = NULL;
    }

    free(line);
    line = NULL;
}

void update_wall_flags(game g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);
    assert(j < game_nb_cols(g) && i >= 0);

    // Get the maximum number of lightbulbs the wall can accept
    int wallLimit = game_get_black_number(g, i, j);
    // If there is a limit verify it
    if (wallLimit != -1) {
        uint sizeOfCells = 0;

        game_cell *ajacent_cells = get_ajacent_cells(g, i, j, &sizeOfCells);

        // Find the number of ajacent lightbulbs
        int noAjacentLightbulbs = 0;
        for (uint x = 0; x < sizeOfCells; x++) {
            if (game_is_lightbulb(g, ajacent_cells[x].row,
                                  ajacent_cells[x].col))
                noAjacentLightbulbs++;
        }

        if (noAjacentLightbulbs > wallLimit)
            game_set_square(g, i, j, (game_get_state(g, i, j) | F_ERROR));
        else {
            // If the ajacent lightbulbs havent caused an error
            // check if other (non-ajacent) lightbulbs cause an error
            int noAvailableValidLightbulbSpots = sizeOfCells;

            for (uint x = 0; x < sizeOfCells; x++) {
                uint row = ajacent_cells[x].row;
                uint col = ajacent_cells[x].col;
                if (game_is_black(g, row, col) || game_is_lighted(g, row, col))
                    noAvailableValidLightbulbSpots--;
            }

            // If the number of lightbulbs that can be placed will be less
            // the required amount the wall is flagged as in error
            if (noAjacentLightbulbs + noAvailableValidLightbulbSpots <
                wallLimit)
                game_set_square(g, i, j, (game_get_state(g, i, j) | F_ERROR));
        }

        if (ajacent_cells != NULL) {
            free(ajacent_cells);
            ajacent_cells = NULL;
        }
    }
}

void remove_all_flags(game g) {
    // Validate parameters
    assert(g);

    // Set square value of each square to state value
    for (uint row = 0; row < game_nb_rows(g); row++) {
        for (uint column = 0; column < game_nb_cols(g); column++) {
            game_set_square(g, row, column, game_get_state(g, row, column));
        }
    }
}

void game_update_flags(game g) {
    // Validate parameters
    assert(g);

    remove_all_flags(g);

    // Check each square is valid
    for (uint row = 0; row < game_nb_rows(g); row++) {
        for (uint column = 0; column < game_nb_cols(g); column++) {
            if (game_is_lightbulb(g, row, column)) {
                // Add light to lightbulb
                game_set_square(g, row, column,
                                (game_get_square(g, row, column) | F_LIGHTED));
                update_lightbulb_flags(g, row, column);
            }
        }
    }

    for (uint row = 0; row < game_nb_rows(g); row++) {
        for (uint column = 0; column < game_nb_cols(g); column++) {
            if (game_is_black(g, row, column)) {
                update_wall_flags(g, row, column);
            }
        }
    }
}

bool game_is_over(cgame g) {
    // Validate parameters
    assert(g);

    // Check each square is valid
    for (uint row = 0; row < game_nb_rows(g); row++) {
        for (uint column = 0; column < game_nb_cols(g); column++) {
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
    assert(g);

    for (uint row = 0; row < game_nb_rows(g); row++) {
        for (uint column = 0; column < game_nb_cols(g); column++) {
            if (game_is_black(g, row, column)) {
                if (game_has_error(g, row, column)) {
                    game_set_square(g, row, column,
                                    game_get_state(g, row, column));
                }
            } else {
                game_set_square(g, row, column, S_BLANK);
            }
        }
    }

    // Clear undo and redo queues
    queue_clear_full(g->undo_queue, free);
    queue_clear_full(g->redo_queue, free);
}
