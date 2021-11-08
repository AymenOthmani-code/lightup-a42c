
# lightup-a42c

Membres du projet :

* Taleiven Kattan taleiven.kattan@etu.u-bordeaux.fr
* Shams Azarfane shams-dyn.azarfane@etu.u-bordeaux.fr
* Aymen Othmani aymen.othmani@etu.u-bordeaux.fr

## Tests

Number of tests: 24

### game_aux.h

|Function|Description|Difficulty|Responsible|State [TODO/DOING/DONE]|
|---|---|---|---|---|
|void game_print(cgame g) |Prints game |Easy |Aymen |TODO |
|game game_default(void) |Creates a default game |Medium |Aymen |TODO |
|game game_default_solution(void) |Creates a default game with solution |Medium |Aymen |TODO |

#### Description of functions - game_aux.h

##### game_print

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Check that the function is called without any runtime errors on the default game and the default game solution. No need to test returned values/objects.

##### game_default

**Time:** 3/5 \
**Complexity :** 1/5 \
**Description:**
Check that every square in the returned game have the correct value for state and/or flag.

#### game_default_solution

**Time:** 2/5 \
**Complexity :** 1/5 \
**Description:**
Check that every square in the returned game have the correct value for state and/or flag.

### game.h

|Function|Description|Difficulty|Responsible|State [TODO/DOING/DONE]|
|---|---|---|---|---|
|game game_new(square *squares) |Creates a new game with default size and initializes it |Medium/Hard |Shams |TODO|
|game game_new_empty(void) |Creates a new empty game with defaut size |Easy |Shams |TODO|
|game game_copy(cgame g) |Duplicates a game |Easy |Shams |TODO|
|bool game_equal(cgame g1, cgame g2) |Tests if two games are equal (same states and same flags) |Easy |Shams |TODO|
|void game_delete(game g) |Deletes the game and frees the allocated memory |Easy ||TODO|
|void game_set_square(game g, uint i, uint j, square s) |Sets the value of a given square |||TODO|
|square game_get_square(cgame g, uint i, uint j) |Gets the raw value of a given square |||TODO|
|square game_get_state(cgame g, uint i, uint j) |Gets the state of a given square |||TODO|
|square game_get_flags(cgame g, uint i, uint j) |Gets the flags of a given square |||TODO|
|bool game_is_blank(cgame g, uint i, uint j) |Test if a given square is blank |||TODO|
|bool game_is_lightbulb(cgame g, uint i, uint j) |Test if a given square is a lightbulb |||TODO|
|bool game_is_black(cgame g, uint i, uint j) |Test if a given square is black (whether or not it is numbered) |||TODO|
|int game_get_black_number(cgame g, uint i, uint j) |Get the number of lightbulbs expected against a black wall |||TODO|
|bool game_is_marked(cgame g, uint i, uint j) |Test if a given square is marked (as not-a-light) |||TODO|
|bool game_is_lighted(cgame g, uint i, uint j) |Test if a given square is lighted |||TODO|
|bool game_has_error(cgame g, uint i, uint j) |Test if a given square has an error flag |||TODO|
|bool game_check_move(cgame g, uint i, uint j, square s) |Checks if a given move is legal |||TODO|
|void game_play_move(game g, uint i, uint j, square s) |Plays a move in a given square |||TODO|
|void game_update_flags(game g) |Update all grid flags |||TODO|
|bool game_is_over(cgame g) |Checks if the game is won |||TODO|
|void game_restart(game g) |Restarts a game |||TODO|

#### Description of functions - game.h

##### game_new

**Time:** 2/5 \
**Complexity :** 3/5 \
**Description:**
Create several lists of predefined squares and check that they return the correct game when passed as parameters. Game default and game default can be two and the third should try to have different characteristics to the others. \
Optional: Create a random square list generator that will generate a list with a random number of black squares and will use the same list to check the returned game. \
Note: Create a function that takes a square list and a game and checks if they are identical. To create the list of squares to use create a function that returns a list of lists to use.

##### game_new_empty

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Check that the returned game is completely empty.

##### game_copy

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Check that the returned game is identical to the game passed in parameter. Should use the same specs for the games as in game_new (see game_new note). Can also implement optional part from game_new. \
Note: Can use game_equal to check that the two games are identical. See note on game_equal

##### game_equal

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Create two new games using game_new and the same list of squares. Verify that it returns true when passed as parameter. Should use the same specs for the games as in game_new (see game_new note). Can also implement optional part from game_new. \
Create two new games using game_new and two different list of squares. Verify that it returns false when passed as parameter.

##### game_delete

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_delete

##### game_set_square

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_set_square

##### game_get_square

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_get_square

##### game_get_state

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_get_state

##### game_get_flags

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_get_flags

##### game_is_blank

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_is_blank

##### game_is_lightbulb

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_is_lightbulb

##### game_is_black

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_is_black

##### game_get_black_number

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_get_black_number

##### game_is_marked

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_is_marked

##### game_is_lighted

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_is_lighted

##### game_has_error

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_has_error

##### game_check_move

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_check_move

##### game_play_move

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_play_move

##### game_update_flags

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_update_flags

##### game_is_over

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_is_over

##### game_restart

**Time:** X/5 \
**Complexity :** X/5 \
**Description:**
Description of game_restart
