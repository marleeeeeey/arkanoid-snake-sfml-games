file(GLOB STATIC_SRCS src/*.cpp)

set(PCH ../game_pch/GamePch.cpp)

add_static_library(utils)