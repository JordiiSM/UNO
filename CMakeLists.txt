cmake_minimum_required(VERSION 3.10)
project(untitled1 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled1 main.c baraja.c baraja.h players.h hands.h game.h game.c confplayers.h confplayers.c conf.h conf.c CLIplayer.h CLIplayer.c)