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

    /*
    In the following switch the default case is mandatory and seeing as we are
    not dealing with errors we will not have a scenario where the state of the
    square is anything other than the 6 states covered by the switch.
    Note: In the coverage file the line 271 and 272 on not shown as covered even
    though they are (a bug maybe!).
    */
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

void game_add_flags(game g, uint i, uint j, square s) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);
    assert(j < game_nb_cols(g) && i >= 0);
    assert(s == F_ERROR || s == F_LIGHTED || s == (F_LIGHTED | F_ERROR));

    game_set_square(g, i, j, (game_get_square(g, i, j) | s));
}

void game_set_flags(game g, uint i, uint j, square s) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);
    assert(j < game_nb_cols(g) && i >= 0);
    assert(s == F_ERROR || s == F_LIGHTED || s == (F_LIGHTED | F_ERROR));

    game_set_square(g, i, j, (game_get_state(g, i, j) | s));
}

game_cell *get_ajacent_cells(game g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);
    assert(j < game_nb_cols(g) && i >= 0);

    // Initialise variables
    game_cell up = {.col = j, .row = i - 1};
    game_cell right = {.col = j + 1, .row = i};
    game_cell down = {.col = j, .row = i + 1};
    game_cell left = {.col = j - 1, .row = i};

    game_cell ajacent_cells[] = {up, right, down, left};

    // If wrapping then wrap cells otherwise set the cells to the default value
    for (uint direction = 0; direction < 4; direction++) {
        // Is the cell off the left side
        if (ajacent_cells[direction].col < 0) {
            if (game_is_wrapping(g))  // Send the cell to the right of the game
                ajacent_cells[direction].col = game_nb_cols(g) - 1;
            else {
                ajacent_cells[direction].col = -1;
                ajacent_cells[direction].row = -1;
            }
        }
        // Is the cell off the top side
        if (ajacent_cells[direction].row < 0) {
            if (game_is_wrapping(g))  // Send the cell to the bottom of the game
                ajacent_cells[direction].row = game_nb_rows(g) - 1;
            else {
                ajacent_cells[direction].col = -1;
                ajacent_cells[direction].row = -1;
            }
        }
        // Is the cell off the right side
        if (ajacent_cells[direction].col == game_nb_cols(g)) {
            if (game_is_wrapping(g))  // Send the cell to the left of the game
                ajacent_cells[direction].col = 0;
            else {
                ajacent_cells[direction].col = -1;
                ajacent_cells[direction].row = -1;
            }
        }
        // Is the cell off the bottom side
        if (ajacent_cells[direction].row == game_nb_rows(g)) {
            if (game_is_wrapping(g))  // Send the cell to the top of the game
                ajacent_cells[direction].row = 0;
            else {
                ajacent_cells[direction].col = -1;
                ajacent_cells[direction].row = -1;
            }
        }
    }

    // Allocate memory
    game_cell *cells = (game_cell *)malloc(4 * sizeof(game_cell));
    assert(cells);

    // Assign values of the cells
    for (uint direction = 0; direction < 4; direction++) {
        cells[direction] = ajacent_cells[direction];
    }

    return cells;
}

game_line *get_ajacent_lines(game g, uint i, uint j) {
    // Validate parameters
    assert(g);
    assert(i < game_nb_rows(g) && i >= 0);
    assert(j < game_nb_cols(g) && i >= 0);

    // Allocate memory
    game_line *lines = (game_line *)malloc(4 * sizeof(game_line));
    assert(lines);

    // Set size of the lines depending on if the game is wrapping or not
    if (game_is_wrapping(g)) {
        lines[0].size = game_nb_rows(g) - 1;
        lines[1].size = game_nb_cols(g) - 1;
        lines[2].size = game_nb_rows(g) - 1;
        lines[3].size = game_nb_cols(g) - 1;
    } else {
        lines[0].size = i;
        lines[1].size = game_nb_cols(g) - 1 - j;
        lines[2].size = game_nb_rows(g) - 1 - i;
        lines[3].size = j;
    }

    // UP
    // Allocate memeory for line of cells heading upwards
    lines[0].line = (game_cell *)calloc(lines[0].size, sizeof(game_cell));
    assert(lines[0].line);
    // Initialise first cell (the ajacent cell)
    int x = j;
    int y = i - 1;
    // Set row and column values for each cell
    for (uint z = 0; z < lines[0].size; z++) {
        if (y == -1) y = game_nb_rows(g) - 1;  // Wrap if needed
        lines[0].line[z].row = y--;
        lines[0].line[z].col = x;
    }

    // RIGHT
    // Allocate memeory for line of cells heading right
    lines[1].line = (game_cell *)calloc(lines[1].size, sizeof(game_cell));
    assert(lines[1].line);
    // Initialise first cell (the ajacent cell)
    x = j + 1;
    y = i;
    // Set row and column values for each cell
    for (uint z = 0; z < lines[1].size; z++) {
        if (x == game_nb_cols(g)) x = 0;  // Wrap if needed
        lines[1].line[z].row = y;
        lines[1].line[z].col = x++;
    }

    // DOWN
    // Allocate memeory for line of cells heading down
    lines[2].line = (game_cell *)calloc(lines[2].size, sizeof(game_cell));
    assert(lines[2].line);
    // Initialise first cell (the ajacent cell)
    x = j;
    y = i + 1;
    // Set row and column values for each cell
    for (uint z = 0; z < lines[2].size; z++) {
        if (y == game_nb_rows(g)) y = 0;  // Wrap if needed
        lines[2].line[z].row = y++;
        lines[2].line[z].col = x;
    }

    // LEFT
    // Allocate memeory for line of cells heading left
    lines[3].line = (game_cell *)calloc(lines[3].size, sizeof(game_cell));
    assert(lines[3].line);
    // Initialise first cell (the ajacent cell)
    x = j - 1;
    y = i;
    // Set row and column values for each cell
    for (uint z = 0; z < lines[3].size; z++) {
        if (x == -1) x = game_nb_cols(g) - 1;  // Wrap if needed
        lines[3].line[z].row = y;
        lines[3].line[z].col = x--;
    }

    return lines;
}

// Applies the effect of the lightbulb on the current square
// Return if light should stop or not
bool apply_effect_of_lightbulb(game g, uint i, uint j) {
    // light up blank or marked flags
    if (game_is_blank(g, i, j) || game_is_marked(g, i, j)) {
        game_set_flags(g, i, j, F_LIGHTED);
        return false;
    } else if (game_is_lightbulb(g, i, j)) {
        // colliding with another lightbulb causes an error
        game_set_flags(g, i, j, (F_LIGHTED | F_ERROR));
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

    // For each line in the array of lines (up = 0, down = 2, right = 1 and left
    // = 3)
    for (uint direction = 0; direction < 4; direction++) {
        for (uint cell = 0; cell < line[direction].size; cell++) {
            if (apply_effect_of_lightbulb(g, line[direction].line[cell].row,
                                          line[direction].line[cell].col))
                break;
        }
        free(line[direction].line);
        line[direction].line = NULL;
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
        game_cell *ajacent_cells = get_ajacent_cells(g, i, j);

        // Find the number of ajacent lightbulbs
        int noAjacentLightbulbs = 0;
        for (uint direction = 0; direction < 4; direction++) {
            int row = ajacent_cells[direction].row;
            int col = ajacent_cells[direction].col;
            if (row != -1 && col != -1) {
                if (game_is_lightbulb(g, row, col)) noAjacentLightbulbs++;
            }
        }

        // Too many lightbulbs next to wall
        if (noAjacentLightbulbs > wallLimit)
            game_set_flags(g, i, j, F_ERROR);
        else {  // Check that non-ajacent lightbulbs don't cause an error
            int noAvailableValidLightbulbSpots = 4;

            for (uint direction = 0; direction < 4; direction++) {
                int row = ajacent_cells[direction].row;
                int col = ajacent_cells[direction].col;
                if (row == -1 && col == -1)  // If the cell is invalid
                    noAvailableValidLightbulbSpots--;
                else
                    // A wall will remove the number of lights we can place
                    // A lighted square will cause an error if we try to place a
                    // lightbulb in the square
                    if (game_is_black(g, row, col) ||
                        game_is_lighted(g, row, col))
                    noAvailableValidLightbulbSpots--;
            }

            // If the number of lightbulbs that can be placed and ahve been
            // placed is less than required amount of lightbulbs the wall is
            // flagged as in error
            if (noAjacentLightbulbs + noAvailableValidLightbulbSpots <
                wallLimit)
                game_set_flags(g, i, j, F_ERROR);
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

    // Ensure the current flags doesn't mess with the update
    remove_all_flags(g);

    // Check each square for a lightbulb
    for (uint row = 0; row < game_nb_rows(g); row++) {
        for (uint column = 0; column < game_nb_cols(g); column++) {
            if (game_is_lightbulb(g, row, column)) {
                game_add_flags(g, row, column, F_LIGHTED);
                // Light the ajacent lines of squares
                update_lightbulb_flags(g, row, column);
            }
        }
    }

    // Note: updating the flags for the walls are in a separate for loop as we
    // need to have all the squares lit in order to simplify the
    // calculations for the wall error flags Check each square for a wall

    // Check each square for a wall
    for (uint row = 0; row < game_nb_rows(g); row++) {
        for (uint column = 0; column < game_nb_cols(g); column++) {
            if (game_is_black(g, row, column)) {
                // Check the ajacent squares and toggle the error flag if needed
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

            /*
            Test coverage shows only first line of a multiple switch statement
            as being covered - all cases are covered.
            The default case is not covered as we cover all expected cases in
            the switch and we do not deal with error cases.
            */
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
