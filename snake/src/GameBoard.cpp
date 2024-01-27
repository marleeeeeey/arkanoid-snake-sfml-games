#include "GameBoard.h"

GameBoard::GameBoard()
{}

void GameBoard::setup( const sf::Vector2u& windowSize )
{
    windowSize_ = windowSize;

    background_.setSize( sf::Vector2f( static_cast<float>( windowSize.x ), static_cast<float>( windowSize.y ) ) );
    auto& backgroundColor = getConfig<sf::Color, "game.view.background_color">();
    background_.setFillColor( backgroundColor );

    // Optionally, you can set a texture for the background if you have a texture
    // background_.setTexture(&someTexture);
}

void GameBoard::draw( sf::RenderWindow& window ) const
{
    window.draw( background_ );
    // TODO Additional drawing can be added here, such as grid lines or other visual elements
}
