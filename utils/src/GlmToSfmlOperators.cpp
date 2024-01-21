#include <utils/GlmToSfmlOperators.h>

sf::Vector2f& operator+( sf::Vector2f& lhs, const glm::vec2& rhs )
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

sf::Vector2f& operator+=( sf::Vector2f& lhs, const glm::vec2& rhs )
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}
