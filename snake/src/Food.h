#pragma once

class Food
{
public:
    Food();
    void respawn( const sf::Vector2u& windowSize );
    void draw( sf::RenderWindow& window ) const;
    const sf::CircleShape& getShape() const;
private:
    sf::CircleShape shape_;
};
