cmake_minimum_required(VERSION 3.10)
project(jencmart)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(jencmart
        src/abstractPlayer.cpp
        src/abstractPlayer.h
        src/ant.cpp
        src/ant.h
        src/antHill.cpp
        src/antHill.h
        src/botPlayer.cpp
        src/botPlayer.h
        src/command.cpp
        src/command.h
        src/common.h
        src/empty.h
        src/exceptions.h
        src/game.cpp
        src/game.h
        src/gameWrapper.cpp
        src/gameWrapper.h
        src/humanPlayer.cpp
        src/humanPlayer.h
        src/inOut.cpp
        src/inOut.h
        src/main.cpp
        src/map.cpp
        src/map.h
        src/mapElement.h
        src/menu.cpp
        src/menu.h
        src/path.cpp
        src/path.h
        src/wall.h
        )
