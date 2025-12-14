cmake_minimum_required(VERSION 3.15)

project(UltimateTicTacToe C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

add_subdirectory(raylib)

add_executable(utt main.c board.c play.c check_conditions.c talking_with_user.c)

target_link_libraries(utt raylib)
