set(TEST_SRCS
    main.cpp
)
set(PCH
    arkanoid_pch.cpp
)

file(GLOB GAME_SRCS *.cpp)

add_gtest(arkanoid)
add_game(arkanoid)