#pragma once
#include "DefaultObject.h"
#include "IDynamicObject.h"
#include "IBonusOwner.h"
#include "IHaveParent.h"

class Ball : public DefaultObject, public IDynamicObject, public IBonusOwner, public IHaveParent
{
    glm::vec2 m_velocity;
    float m_maxSpeed = getConfig<float>( "game.objects.ball.maxSpeed" );
    float m_slowdownSpeed = m_maxSpeed * 0.75f;
    std::optional<Collision> m_biggestCollision;
    std::optional<BonusType> m_bonusType;
    std::optional<std::shared_ptr<IObject>> m_parent;

    void changeDirection();
    void stealLiveFromOneDestructibleObject( const std::vector<Collision>& collisions ) const;
public:
    Ball();
    void onBumping( std::vector<Collision>& collisions ) override;
    void calcState( std::optional<sf::Event> event, sf::Time elapsedTime ) override;
    void draw( sf::RenderWindow& window ) override;
    std::shared_ptr<IObject> createCopyFromThis() override;
    std::optional<BonusType>& bonusType() override;
    std::string name() override;
    void setParent( std::shared_ptr<IObject> parent ) override;
    void removeParent() override;
    glm::vec2& velocity() override;
};
