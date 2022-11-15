cmake_minimum_required(VERSION 3.23)
project(cppgame)

set(CMAKE_CXX_STANDARD 11)

add_executable(21game 21game/main.cpp)
add_executable(times times/main.cpp)
add_executable(chargame chargame/main.cpp)
add_executable(typegame chargame/typegame.cpp)
add_executable(char_animation chargame/char_animation.cpp)
add_executable(conway_life conway_life/main.cpp)
add_executable(sokoban sokoban/main.cpp)
