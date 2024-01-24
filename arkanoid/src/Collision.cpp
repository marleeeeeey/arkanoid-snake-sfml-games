#include "Collision.h"

namespace
{
float getArea( const sf::Vector2f& size )
{
    return size.x * size.y;
}
} // namespace

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

std::optional<Collision> getBiggestCollision( const std::vector<Collision>& collisions )
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
