file(GLOB GAME_SRCS src/*.cpp)
set(PCH ../game_pch/GameSdlPch.cpp)
add_sdl_game(sdl_game_template)