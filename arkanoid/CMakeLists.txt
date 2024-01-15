# set(TEST_SRCS
#     main.cpp
# )
# add_gtest(arkanoid)

set(PCH
    src/ArkanoidPch.cpp
)

file(GLOB GAME_SRCS src/*.cpp)

add_game(arkanoid)