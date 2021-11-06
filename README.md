
# lightup-a42c

Membres du projet :

* Taleiven Kattan taleiven.kattan@etu.u-bordeaux.fr
* Shams Azarfane shams-dyn.azarfane@etu.u-bordeaux.fr
* Aymen Othmani aymen.othmani@etu.u-bordeaux.fr

## Tests

### game_aux.h

|Function|Description|Difficulty|Responsible|State [TODO/DOING/DONE]|
|---|---|---|---|---|
|void game_print(cgame g) |Prints game |Easy |Aymen |TODO |
|game game_default(void) |Creates a default game |Medium |Aymen |TODO |
|game game_default_solution(void) |Creates a default game with solution |Medium |Shams |TODO |

### game.h

|Function|Description|Difficulty|Responsible|State|
|---|---|---|---|---|
|game game_new(square *squares) |Creates a new game with default size and initializes it |Medium ||TODO|
|game game_new_empty(void) ||||TODO|
|game game_copy(cgame g) ||||TODO|
|bool game_equal(cgame g1, cgame g2) ||||TODO|
|void game_delete(game g) ||||TODO|
|void game_set_square(game g, uint i, uint j, square s) ||||TODO|
|square game_get_square(cgame g, uint i, uint j) ||||TODO|
|square game_get_state(cgame g, uint i, uint j) ||||TODO|
|square game_get_flags(cgame g, uint i, uint j) ||||TODO|
|bool game_is_blank(cgame g, uint i, uint j) ||||TODO|
|bool game_is_lightbulb(cgame g, uint i, uint j) ||||TODO|
|bool game_is_black(cgame g, uint i, uint j) ||||TODO|
|int game_get_black_number(cgame g, uint i, uint j) ||||TODO|
|bool game_is_marked(cgame g, uint i, uint j) ||||TODO|
|bool game_is_lighted(cgame g, uint i, uint j) ||||TODO|
|bool game_has_error(cgame g, uint i, uint j) ||||TODO|
|bool game_check_move(cgame g, uint i, uint j, square s) ||||TODO|
|void game_play_move(game g, uint i, uint j, square s) ||||TODO|
|void game_update_flags(game g) ||||TODO|
|bool game_is_over(cgame g) ||||TODO|
|void game_restart(game g) ||||TODO|
