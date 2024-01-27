#include "Food.h"

namespace
{
auto& cellSize = getConfig<float, "game.view.cell_size_px">();
}

Food::Food()
{
    auto& foodColor = getConfig<sf::Color, "game.objects.food.color">();
    shape_.setRadius( cellSize / 2 );
    shape_.setFillColor( foodColor );
}

void Food::respawn( const sf::Vector2u& windowSize )
{
    auto x = roundStep<int>( glm::linearRand<int>( 0, windowSize.x ), cellSize );
    auto y = roundStep<int>( glm::linearRand<int>( 0, windowSize.y ), cellSize );
    shape_.setPosition( x, y );
}

void Food::draw( sf::RenderWindow& window ) const
{
    window.draw( shape_ );
}

const sf::CircleShape& Food::getShape() const
{
    return shape_;
}
