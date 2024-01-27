#pragma once

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

bool isOppositeDirection( Direction direction1, Direction direction2 );