cmake_minimum_required(VERSION 2.6)
project(lightup C)

set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
add_executable(game_text game_text.c)

add_library(game game.o game_aux.c)
target_link_libraries(game_text game)
