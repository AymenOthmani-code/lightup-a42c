cmake_minimum_required(VERSION 2.6)

project(lightup C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
add_executable(game_text game_text.c)
add_executable(game_test_tkattan game_test_tkattan.c)
add_executable(game_test_aothmani game_test_aothmani.c)
add_executable(game_test_sazarfane game_test_sazarfane.c)

add_library(game game.o game_aux.c)
target_link_libraries(game_text game)
target_link_libraries(game_test_tkattan game)
target_link_libraries(game_test_aothmani game)
target_link_libraries(game_test_sazarfane game)

add_test(test_tkattan_dummy ./game_test_tkattan dummy)

add_test(test_aothmani_dummy ./game_test_aothmani dummy)

add_test(test_game_new ./game_test_sazarfane game_new)
add_test(test_game_new_empty ./game_test_sazarfane game_new_empty)
add_test(test_game_copy ./game_test_sazarfane game_copy)
add_test(test_game_equal ./game_test_sazarfane game_equal)
add_test(test_game_set_square ./game_test_sazarfane game_set_square)
add_test(test_game_is_black ./game_test_sazarfane game_is_black)
add_test(test_game_get_black_number ./game_test_sazarfane game_get_black_number)
add_test(test_game_is_marked ./game_test_sazarfane game_is_marked)