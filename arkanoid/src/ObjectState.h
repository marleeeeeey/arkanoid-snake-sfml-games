#pragma once

class ObjectState
{
    bool m_destroyFlag;
    sf::Time m_timeStep;
    sf::RectangleShape m_collisionRect;
public:
    ObjectState();

    sf::RectangleShape getCollisionRect() const;
    void setCollisionRect( const sf::RectangleShape& collisionRect );
    void setCollisionRect( const sf::Vector2f& size, const sf::Vector2f& pos );

    void setPos( const sf::Vector2f& pos );
    sf::Vector2f getPos() const;

    void setSize( const sf::Vector2f& size );
    sf::Vector2f getSize() const;

    void setDestroyFlag( bool isDestroyed );
    bool getDestroyFlag() const;

    // TODO: think if needed to keep timeStep for every ObjectState
    void setTimeStep( const sf::Time& timeStep );
    sf::Time getTimeStep() const;
};
