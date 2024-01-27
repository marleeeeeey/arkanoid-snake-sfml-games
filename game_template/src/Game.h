#pragma once

class Game
{
public:
    Game();
    void setup();
    void update( const sf::Time& deltaTime );
    void render( sf::RenderWindow& window );
    [[nodiscard]] bool isGameOver() const;
};
