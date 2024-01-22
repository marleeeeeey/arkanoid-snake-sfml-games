#include "DefaultObject.h"

namespace
{

// Return true if two objects have collision. Return false if two objects are the same.
bool haveCollision( const std::shared_ptr<IObject>& objectA, const std::shared_ptr<IObject>& objectB )
{
    if ( objectA == objectB )
        return false;

    return calcIntersectRectShape( objectA->state().getCollisionRect(), objectB->state().getCollisionRect() )
        .has_value();
}

template <typename ObjectCollection>
bool haveCollision( const std::shared_ptr<IObject>& object, const ObjectCollection& secondaryObjects )
{
    return std::ranges::any_of(
        secondaryObjects, [&]( const auto& secondaryObject ) { return haveCollision( object, secondaryObject ); } );
}

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
} // namespace

void DefaultObject::onBumping( std::vector<Collision>& collisions )
{
    // TODO: remove this method (do nothing).
}

void DefaultObject::calcState( std::optional<sf::Event> event, sf::Time elapsedTime )
{
    // TODO: remove this method (do nothing).
}

void DefaultObject::draw( sf::RenderWindow& window )
{
    // TODO: remove this method (do nothing).
}

ObjectState& DefaultObject::state()
{
    return m_state;
}

void DefaultObject::saveState()
{
    m_savedState = m_state;
}

void DefaultObject::restoreState()
{
    if ( m_savedState )
    {
        m_state = m_savedState.value();
        m_savedState = {};
    }
}

bool DefaultObject::isVisible()
{
    return true;
}

void DefaultObject::setOnBumpingCallBack( OnBumpingCallback cb )
{
    m_onBumpingCallback = cb;
}

bool DefaultObject::haveCollisions( const std::set<std::shared_ptr<IObject>>& objects )
{
    return haveCollision( shared_from_this(), objects );
}

void DefaultObject::checkBumping( std::vector<std::shared_ptr<IObject>>& objects )
{
    auto thisObject = shared_from_this();
    auto collisions = getCollisions( thisObject, objects );
    onBumping( collisions );
    if ( m_onBumpingCallback )
        m_onBumpingCallback( thisObject, collisions );
    m_onBumpingCallback = {};
}
