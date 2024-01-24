#include "ObjectState.h"

ObjectState::ObjectState()
{
    m_destroyFlag = false;
}

sf::RectangleShape ObjectState::getCollisionRect() const
{
    return m_collisionRect;
}

void ObjectState::setCollisionRect( const sf::RectangleShape& collisionRect )
{
    m_collisionRect = collisionRect;
}

void ObjectState::setCollisionRect( const sf::Vector2f& size, const sf::Vector2f& pos )
{
    m_collisionRect = createRectangleShape( size, pos );
}

void ObjectState::setPos( const sf::Vector2f& pos )
{
    m_collisionRect = createRectangleShape( getSize(), pos );
}

sf::Vector2f ObjectState::getPos() const
{
    return m_collisionRect.getPosition();
}

void ObjectState::setSize( const sf::Vector2f& size )
{
    m_collisionRect = createRectangleShape( size, getPos() );
}

sf::Vector2f ObjectState::getSize() const
{
    return m_collisionRect.getSize();
}

void ObjectState::setDestroyFlag( bool isDestroyed )
{
    m_destroyFlag = isDestroyed;
}

bool ObjectState::getDestroyFlag() const
{
    return m_destroyFlag;
}
