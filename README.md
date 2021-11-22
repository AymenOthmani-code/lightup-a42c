
# lightup-a42c

Membres du projet :

* Taleiven Kattan taleiven.kattan@etu.u-bordeaux.fr
* Shams Azarfane shams-dyn.azarfane@etu.u-bordeaux.fr
* Aymen Othmani aymen.othmani@etu.u-bordeaux.fr

## Functions

|Function|Description|Branch|Responsible|
|---|---|---|---|
|game game_new(square *squares) |Creates a new game with default size and initializes it |dev_alloc_game |Aymen |
|game game_new_empty(void) |Creates a new empty game with defaut size |dev_alloc_game |Aymen |
|void game_delete(game g) |Deletes the game and frees the allocated memory |dev_alloc_game |Aymen |
|void game_restart(game g) |Restarts a game |dev_game_restart |Aymen |
|bool game_check_move(cgame g, uint i, uint j, square s) |Checks if a given move is legal |dev_game_check_move |Aymen |
|void game_set_square(game g, uint i, uint j, square s) |Sets the value of a given square |dev_game_get_set |Shams |
|square game_get_square(cgame g, uint i, uint j) |Gets the raw value of a given square |dev_game_get_set |Shams |
|square game_get_state(cgame g, uint i, uint j) |Gets the state of a given square |dev_game_get_set |Shams |
|square game_get_flags(cgame g, uint i, uint j) |Gets the flags of a given square |dev_game_get_set |Shams |
|int game_get_black_number(cgame g, uint i, uint j) |Get the number of lightbulbs expected against a black wall |dev_game_get_set |Shams |
|bool game_is_blank(cgame g, uint i, uint j) |Test if a given square is blank |dev_game_is_has |Shams |
|bool game_is_lightbulb(cgame g, uint i, uint j) |Test if a given square is a lightbulb |dev_game_is_has |Shams |
|bool game_is_black(cgame g, uint i, uint j) |Test if a given square is black (whether or not it is numbered) |dev_game_is_has |Shams |
|bool game_is_marked(cgame g, uint i, uint j) |Test if a given square is marked (as not-a-light) |dev_game_is_has |Shams |
|bool game_is_lighted(cgame g, uint i, uint j) |Test if a given square is lighted |dev_game_is_has |Shams |
|bool game_has_error(cgame g, uint i, uint j) |Test if a given square has an error flag |dev_game_is_has |Shams |
|game game_copy(cgame g) |Duplicates a game |dev_game_copy_equal |Taleiven |
|bool game_equal(cgame g1, cgame g2) |Tests if two games are equal (same states and same flags) |dev_game_copy_equal |Taleiven |
|bool game_is_over(cgame g) |Checks if the game is won |dev_game_is_over |Taleiven |
|void game_play_move(game g, uint i, uint j, square s) |Plays a move in a given square |dev_play_update_flags |Taleiven |
|void game_update_flags(game g) |Update all grid flags |dev_play_update_flags |Taleiven |

## Tests

Number of tests: 24

### game_aux.h

|Function|Description|Difficulty|Responsible|
|---|---|---|---|
|void game_print(cgame g) |Prints game |Easy |Aymen |
|game game_default(void) |Creates a default game |Medium |Aymen |
|game game_default_solution(void) |Creates a default game with solution |Medium |Aymen |

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

|Function|Description|Difficulty|Responsible|
|---|---|---|---|
|game game_new(square *squares) |Creates a new game with default size and initializes it |Medium/Hard |Shams |
|game game_new_empty(void) |Creates a new empty game with defaut size |Easy |Shams |
|game game_copy(cgame g) |Duplicates a game |Easy |Shams |
|bool game_equal(cgame g1, cgame g2) |Tests if two games are equal (same states and same flags) |Easy |Shams |
|void game_delete(game g) |Deletes the game and frees the allocated memory |Easy |Aymen |
|void game_set_square(game g, uint i, uint j, square s) |Sets the value of a given square |Medium |Shams |
|square game_get_square(cgame g, uint i, uint j) |Gets the raw value of a given square |Medium |Aymen |
|square game_get_state(cgame g, uint i, uint j) |Gets the state of a given square |Medium |Shams |
|square game_get_flags(cgame g, uint i, uint j) |Gets the flags of a given square |Medium |Aymen |
|bool game_is_blank(cgame g, uint i, uint j) |Test if a given square is blank |Easy |Aymen |
|bool game_is_lightbulb(cgame g, uint i, uint j) |Test if a given square is a lightbulb |Easy |Aymen |
|bool game_is_black(cgame g, uint i, uint j) |Test if a given square is black (whether or not it is numbered) |Easy |Shams |
|int game_get_black_number(cgame g, uint i, uint j) |Get the number of lightbulbs expected against a black wall |Easy |Shams |
|bool game_is_marked(cgame g, uint i, uint j) |Test if a given square is marked (as not-a-light) |Easy |Shams |
|bool game_is_lighted(cgame g, uint i, uint j) |Test if a given square is lighted |Easy |Aymen |
|bool game_has_error(cgame g, uint i, uint j) |Test if a given square has an error flag |Easy |Aymen |
|bool game_check_move(cgame g, uint i, uint j, square s) |Checks if a given move is legal |Hard |Taleiven |
|void game_play_move(game g, uint i, uint j, square s) |Plays a move in a given square |Hard |Taleiven |
|void game_update_flags(game g) |Update all grid flags |Hard |Taleiven |
|bool game_is_over(cgame g) |Checks if the game is won |Hard |Taleiven |
|void game_restart(game g) |RestartPs a game |Hard |Taleiven |

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
Create two new games using game_new and two different list of squares. Verify that it returns false when passed as parameter. \
Note: As all game_new, game_copy and game_equal will use more or less the same lists of squares a function can be made to return a list of a list of squares.

##### game_delete

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Check that the function is called without any runtime errors on the default game and the default game solution.

##### game_set_square

**Time:** 2/5 \
**Complexity :** 1/5 \
**Description:**
Take the an empty game and check that when the different available states/flags/squares are added the are correct and dont modify anthing else around it.

##### game_get_square

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Get the squares from the default game and check they are what we expect them to be.
Note: Ask teacher about the fact that this is already tested in many other functions.

##### game_get_state

**Time:** 2/5 \
**Complexity :** 1/5 \
**Description:**
Set squares to different values with mixes of states and flags (all combinations should be covered) and check that only the correct state is returned (not the flags).

##### game_get_flags

**Time:** 2/5 \
**Complexity :** 1/5 \
**Description:**
Set squares to different values with mixes of states and flags (all combinations should be covered) and check that only the correct flag is returned (not the state).

##### game_is_blank

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Set a square to the correct value, set another square to the other possible non correct values (all combinations of states and flags should be tested) and test for correctness.

##### game_is_lightbulb

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Set a square to the correct value, set another square to the other possible non correct values (all combinations of states and flags should be tested) and test for correctness.

##### game_is_black

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Set a square to the correct value, set another square to the other possible non correct values (all combinations of states and flags should be tested) and test for correctness.

##### game_get_black_number

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Set a square to the correct value, set another square to the other possible non correct values (all combinations of states and flags should be tested) and test for correctness.

##### game_is_marked

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Set a square to the correct value, set another square to the other possible non correct values (all combinations of states and flags should be tested) and test for correctness.

##### game_is_lighted

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Set a square to the correct value, set another square to the other possible non correct values (all combinations of states and flags should be tested) and test for correctness.

##### game_has_error

**Time:** 1/5 \
**Complexity :** 1/5 \
**Description:**
Set a square to the correct value, set another square to the other possible non correct values (all combinations of states and flags should be tested) and test for correctness.

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
