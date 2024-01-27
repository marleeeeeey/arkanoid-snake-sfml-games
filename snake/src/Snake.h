#pragma once
#include "Food.h"

class Snake
{
public:
    Snake();
    void setup( const sf::Vector2u& windowSize );
    void update( const sf::Time& deltaTime );
    void grow();
    void changeDirection( Direction newDirection );
    void draw( sf::RenderWindow& window ) const;
    [[nodiscard]] bool collidesWith( const Food& food ) const;
    [[nodiscard]] bool collidesWithScreenArea() const;
    [[nodiscard]] bool collidesWithSelf() const;
private:
    sf::Vector2u windowSize_;
    std::vector<sf::RectangleShape> body_;
    Direction direction_;
    float movementValue_;
};
