# set(TEST_SRCS
#     main.cpp
# )
# add_gtest(arkanoid)

file(GLOB GAME_SRCS src/*.cpp)

set(PCH ../game_pch/GamePch.cpp)

add_game(arkanoid)