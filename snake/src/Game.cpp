#include "Game.h"

Game::Game()
{}

void Game::setup( const sf::Vector2u& windowSize )
{
    windowSize_ = windowSize;
    snake_.setup( windowSize_ );
    gameBoard_.setup( windowSize_ );
    food_.respawn( windowSize_ );
    scoreBoard_.reset();
    gameOver_ = false;
}

void Game::update( const sf::Time& deltaTime )
{
    if ( !gameOver_ )
    {
        snake_.update( deltaTime );
        if ( snake_.collidesWithScreenArea() || snake_.collidesWithSelf() )
        {
            gameOver_ = true;
            return;
        }

        if ( snake_.collidesWith( food_ ) )
        {
            snake_.grow();
            food_.respawn( windowSize_ );
            scoreBoard_.updateScore( 1 );
        }
    }
}

void Game::render( sf::RenderWindow& window ) const
{
    gameBoard_.draw( window );
    snake_.draw( window );
    food_.draw( window );
    scoreBoard_.draw( window );
}

bool Game::isGameOver() const
{
    return gameOver_;
}

void Game::handleInput( const sf::Event& event )
{
    static const std::map<sf::Keyboard::Key, Direction> keyboardToDirectionMap = {
        { sf::Keyboard::Key::Up, Direction::Up },
        { sf::Keyboard::Key::Down, Direction::Down },
        { sf::Keyboard::Key::Left, Direction::Left },
        { sf::Keyboard::Key::Right, Direction::Right } };

    if ( event.type == sf::Event::KeyPressed && keyboardToDirectionMap.contains( event.key.code ) )
        snake_.changeDirection( keyboardToDirectionMap.at( event.key.code ) );
}
