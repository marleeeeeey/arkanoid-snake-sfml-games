#include "Wall.h"

void Wall::draw( sf::RenderWindow& window )
{
    auto shape = state().getCollisionRect();
    shape.setFillColor( sf::Color::Green );
    window.draw( shape );
}

std::shared_ptr<IObject> Wall::clone()
{
    return std::make_shared<Wall>( *this );
}

std::string Wall::name()
{
    return "Wall";
}
