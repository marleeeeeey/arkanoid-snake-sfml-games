file(GLOB GAME_SRCS src/*.cpp)
set(PCH ../game_pch/GameSfmlPch.cpp)
add_sfml_game(sfml_game_template)