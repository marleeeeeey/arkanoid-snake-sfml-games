#pragma once

class GameBoard
{
public:
    GameBoard();
    void setup( const sf::Vector2u& windowSize );
    void draw( sf::RenderWindow& window ) const;
private:
    sf::Vector2u windowSize_;
    sf::RectangleShape background_;
};
