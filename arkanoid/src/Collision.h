#pragma once

class IObject;

class Collision
{
    std::shared_ptr<IObject> m_object;
    sf::RectangleShape m_collisionRect;
public:
    Collision( std::shared_ptr<IObject> object, sf::RectangleShape collisionRect );
    Collision( const Collision& other ) = default;
    std::shared_ptr<IObject> getObject();
    sf::RectangleShape getCollisionRect() const;
};

template <typename CollisionCollection>
std::optional<Collision> getBiggestCollision( const CollisionCollection& collisions )
{
    auto itMax = std::ranges::max_element(
        collisions,
        []( const Collision& lhs, const Collision& rhs )
        {
            auto areaLhs = getArea( lhs.getCollisionRect().getSize() );
            auto areaRhs = getArea( rhs.getCollisionRect().getSize() );
            return areaLhs < areaRhs;
        } );

    if ( itMax != collisions.end() )
    {
        return *itMax;
    }

    return {};
}

// TODO: remove hack with include in the middle of the file.
#include "IObject.h"

template <typename ObjectCollection>
std::vector<Collision> getCollisions( const std::shared_ptr<IObject>& object, const ObjectCollection& secondaryObjects )
{
    std::vector<Collision> collisions;
    for ( const auto& secondaryObject : secondaryObjects )
    {
        // Skip self.
        if ( object == secondaryObject )
            continue;

        // Add collision if exists.
        if ( auto collision = calcIntersectRectShape(
                 object->state().getCollisionRect(), secondaryObject->state().getCollisionRect() ) )
        {
            collisions.emplace_back( secondaryObject, collision.value() );
        }
    }

    return collisions;
}