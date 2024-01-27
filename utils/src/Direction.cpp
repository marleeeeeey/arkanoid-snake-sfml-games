#include <utils/Direction.h>

bool isOppositeDirection( Direction direction1, Direction direction2 )
{
    return ( direction1 == Direction::Up && direction2 == Direction::Down ) ||
        ( direction1 == Direction::Down && direction2 == Direction::Up ) ||
        ( direction1 == Direction::Left && direction2 == Direction::Right ) ||
        ( direction1 == Direction::Right && direction2 == Direction::Left );
}
