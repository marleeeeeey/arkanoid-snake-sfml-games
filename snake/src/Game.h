#pragma once
#include "Snake.h"
#include "Food.h"
#include "GameBoard.h"
#include "ScopeBoard.h"

class Game
{
public:
    explicit Game();
    void setup( const sf::Vector2u& windowSize );
    void update( const sf::Time& deltaTime );
    void render( sf::RenderWindow& window ) const;
    [[nodiscard]] bool isGameOver() const;
    void handleInput( const sf::Event& event );
private:
    Snake snake_;
    Food food_;
    GameBoard gameBoard_;
    ScoreBoard scoreBoard_;
    bool gameOver_ = false;
    sf::Vector2u windowSize_;
};
