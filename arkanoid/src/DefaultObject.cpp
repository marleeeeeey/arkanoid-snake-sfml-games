#include "DefaultObject.h"
#include "HelperFunctions.h"

std::vector<Collision> getCollisions(
    std::shared_ptr<IObject> object, std::vector<std::shared_ptr<IObject>> secondaryObjects )
{
    std::vector<Collision> collisions;
    for ( auto secondaryObject : secondaryObjects )
    {
        if ( object == secondaryObject )
            continue;

        auto collision = hf::getIntersectRectShape(
            object->state().getCollisionRect(), secondaryObject->state().getCollisionRect() );
        if ( collision )
        {
            collisions.emplace_back( secondaryObject, collision.value() );
        }
    }

    return collisions;
}

void DefaultObject::onBumping( std::vector<Collision>& collisions )
{
    // do nothing
}

void DefaultObject::calcState( std::optional<sf::Event> event, sf::Time elapsedTime )
{
    // do nothing
}

void DefaultObject::draw( sf::RenderWindow& window )
{
    // do nothing
}

State& DefaultObject::state()
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
    std::copy( objectsSet.begin(), objectsSet.end(), std::back_inserter( objects ) );
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
