#pragma once

class Game
{
public:
    explicit Game();
    void setup( const sf::Vector2u& windowSize );
    void update( const sf::Time& deltaTime );
    void render( sf::RenderWindow& window ) const;
    [[nodiscard]] bool isGameOver() const;
    void handleInput( const sf::Event& event );
};
