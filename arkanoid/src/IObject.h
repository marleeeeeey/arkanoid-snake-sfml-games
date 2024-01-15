#pragma once
#include "ObjectState.h"
#include "Collision.h"

using OnBumpingCallback =
    std::function<void( std::shared_ptr<IObject> thisObject, std::vector<Collision>& collisions )>;

class IObject : public std::enable_shared_from_this<IObject>
{
public:
    virtual ~IObject() = default;
    virtual std::string name() = 0;
    virtual void checkBumping( std::vector<std::shared_ptr<IObject>>& objects ) = 0;
    virtual void onBumping( std::vector<Collision>& collisions ) = 0;
    virtual void setOnBumpingCallBack( OnBumpingCallback callback ) = 0;
    virtual void calcState( std::optional<sf::Event> event, sf::Time elapsedTime ) = 0;
    virtual void draw( sf::RenderWindow& window ) = 0;
    virtual void saveState() = 0;
    virtual void restoreState() = 0;
    virtual ObjectState& state() = 0;
    virtual std::shared_ptr<IObject> createCopyFromThis() = 0;
    virtual bool isVisible() = 0;
};
