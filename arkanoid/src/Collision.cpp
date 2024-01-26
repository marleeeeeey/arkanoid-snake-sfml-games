#include "Collision.h"

Collision::Collision( std::shared_ptr<IObject> object, sf::RectangleShape collisionRect )
{
    m_object = std::move( object );
    m_collisionRect = std::move( collisionRect );
}

std::shared_ptr<IObject> Collision::getObject()
{
    return m_object;
}

sf::RectangleShape Collision::getCollisionRect() const
{
    return m_collisionRect;
}
