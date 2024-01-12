set(TEST_SRCS
    main.cpp
)

file( GLOB GAME_SRCS *.cpp *.h )


add_gtest(arkanoid)
add_game(arkanoid)