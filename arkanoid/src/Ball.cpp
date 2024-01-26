#include "Ball.h"
#include "IDestructible.h"

namespace
{
const float ballInitialSpeed = getConfig<float, "game.objects.ball.initialSpeed">();
const float ballMaxSpeed = ballInitialSpeed * 1.5f;
const float ballDiameter = getConfig<float, "game.objects.ball.diameter">();
} // namespace

Ball::Ball()
{
    auto angle = glm::linearRand<float>( -70, -50 );
    angle = randomBool() ? angle : -angle;
    m_velocity = vectorFromDirectionAndLength( angle, ballInitialSpeed );
    DefaultObject::state().setSize( { ballDiameter, ballDiameter } );
}

// TODO: move `fixCollisionAndChangeDirection` to utils
// See explanation of evaluations in `arkanoid-uml.io`
void Ball::fixCollisionAndChangeDirection( const Collision& collision )
{
    auto collisionSize = collision.getCollisionRect().getSize();
    auto pos = state().getPos();

    if ( isEqual( collisionSize.x, collisionSize.y ) )
    {
        m_velocity.x *= -1;
        m_velocity.y *= -1;
        pos.y += sign( m_velocity.y ) * collisionSize.y * 2;
        pos.x += sign( m_velocity.x ) * collisionSize.x * 2;
    }
    else if ( collisionSize.x > collisionSize.y )
    {
        m_velocity.y *= -1;
        pos.y += sign( m_velocity.y ) * collisionSize.y * 2;
    }
    else
    {
        m_velocity.x *= -1;
        pos.x += sign( m_velocity.x ) * collisionSize.x * 2;
    }

    state().setPos( pos );
}

bool Ball::shouldFixCollition( const std::shared_ptr<IObject>& collisionObject ) const
{
    if ( m_bonusType && m_bonusType.value() == BonusType::FireBall )
    {
        auto desctuctibleObject = std::dynamic_pointer_cast<IDestructible>( collisionObject );
        if ( !desctuctibleObject || !desctuctibleObject->lives() )
        {
            return true;
        }
    }
    else
    {
        return true;
    }

    return false;
}

void Ball::onBumping( std::vector<Collision>& collisions )
{
    if ( collisions.empty() )
        return;

    // 1. Calculate biggest collision
    auto biggestCollistion = getBiggestCollision( collisions ).value();
    auto collisionObject = biggestCollistion.getObject();

    // 2. Fix collision if needed
    if ( shouldFixCollition( collisionObject ) )
        fixCollisionAndChangeDirection( biggestCollistion );

    // 3. Decrease lives if needed
    auto destructibleCollisionObject = std::dynamic_pointer_cast<IDestructible>( collisionObject );
    if ( destructibleCollisionObject && destructibleCollisionObject->lives() )
        destructibleCollisionObject->lives().value()--;

    // 4. Call responce collision
    for ( auto collision : collisions )
    {
        std::vector<Collision> backwardCollitions;
        backwardCollitions.emplace_back( shared_from_this(), collision.getCollisionRect() );
        collision.getObject()->onBumping( backwardCollitions );
    }
}

void Ball::calcState( std::optional<sf::Event> event, sf::Time elapsedTime )
{
    if ( m_parent )
        return;

    float sec = elapsedTime.asSeconds();

    auto& acceleration_pxps = getConfig<float, "game.objects.ball.acceleration_pxps">();
    m_velocity *= acceleration_pxps;

    if ( glm::length( m_velocity ) > ballMaxSpeed )
        m_velocity = glm::normalize( m_velocity ) * ballMaxSpeed;

    if ( m_bonusType && m_bonusType.value() == BonusType::DecreaseBallSpeed )
    {
        m_bonusType = {};
        m_velocity = glm::normalize( m_velocity ) * ballInitialSpeed;
    }

    auto pos = state().getPos();
    pos += sec * m_velocity;
    state().setPos( pos );
}

void Ball::draw( sf::RenderWindow& window )
{
    float rectSide = state().getCollisionRect().getSize().x;
    float radius = rectSide / std::sqrt( 2.0f );
    auto circleShape = createCircleShape( radius, state().getPos() );

    sf::Color shapeColor;
    if ( m_bonusType && m_bonusType.value() == BonusType::FireBall )
    {
        shapeColor = sf::Color::Red;
    }
    else
    {
        shapeColor = sf::Color::Blue;
    }

    circleShape.setFillColor( shapeColor );
    window.draw( circleShape );
}

std::shared_ptr<IObject> Ball::clone()
{
    return std::make_shared<Ball>( *this );
}

std::optional<BonusType>& Ball::bonusType()
{
    return m_bonusType;
}

std::string Ball::name()
{
    return "Ball";
}

void Ball::setParent( std::shared_ptr<IObject> parent )
{
    m_parent = parent;
}

void Ball::removeParent()
{
    m_parent.reset();
}

glm::vec2& Ball::velocity()
{
    return m_velocity;
}
