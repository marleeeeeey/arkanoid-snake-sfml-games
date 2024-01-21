#include "DefaultObject.h"

std::vector<Collision> getCollisions(
    const std::shared_ptr<IObject>& object, const std::vector<std::shared_ptr<IObject>>& secondaryObjects )
{
    std::vector<Collision> collisions;
    for ( const auto& secondaryObject : secondaryObjects )
    {
        // Skip self.
        if ( object == secondaryObject )
            continue;

        // Add collision if exists.
        if ( auto collision = getIntersectRectShape(
                 object->state().getCollisionRect(), secondaryObject->state().getCollisionRect() ) )
        {
            collisions.emplace_back( secondaryObject, collision.value() );
        }
    }

    return collisions;
}

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
        m_state = m_savedState.value();
}

bool DefaultObject::isVisible()
{
    return true;
}

void DefaultObject::setOnBumpingCallBack( OnBumpingCallback cb )
{
    m_onBumpingCallback = cb;
}

bool DefaultObject::haveCollisions( std::set<std::shared_ptr<IObject>> objectsSet )
{
    std::vector<std::shared_ptr<IObject>> objects;
    std::ranges::copy( objectsSet, std::back_inserter( objects ) );
    auto collisions = getCollisions( shared_from_this(), objects );
    return !collisions.empty();
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
