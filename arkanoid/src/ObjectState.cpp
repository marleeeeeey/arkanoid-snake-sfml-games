#include "ObjectState.h"
#include "HelperFunctions.h"

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
    m_collisionRect = hf::createRectangleShape( size, pos );
}

void ObjectState::setPos( const sf::Vector2f& pos )
{
    m_collisionRect = hf::createRectangleShape( getSize(), pos );
}

sf::Vector2f ObjectState::getPos() const
{
    return m_collisionRect.getPosition();
}

void ObjectState::setSize( const sf::Vector2f& size )
{
    m_collisionRect = hf::createRectangleShape( size, getPos() );
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

void ObjectState::setTimeStep( const sf::Time& timeStep )
{
    m_timeStep = timeStep;
}

sf::Time ObjectState::getTimeStep() const
{
    return m_timeStep;
}
