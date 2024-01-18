#include "Ball.h"
#include "IDestructible.h"

namespace
{
const float ballInitialSpeed = getConfig<float>( "game.objects.ball.initialSpeed" );
const float ballMaxSpeed = ballInitialSpeed * 1.5f;
} // namespace

Ball::Ball()
{
    int angle = randomInt( -70, -50 );
    angle = randomBool() ? angle : -angle;
    m_velocity = vectorFromDirectionAndLength( angle, ballInitialSpeed );
    DefaultObject::state().setSize( { 20, 20 } );
}

float getArea( const sf::Vector2f& size )
{
    return size.x * size.y;
}

Collision getBiggestCollision( std::vector<Collision>& collisions )
{
    std::ranges::sort(
        collisions,
        []( const Collision& lhs, const Collision& rhs )
        {
            auto areaLhs = getArea( lhs.getCollisionRect().getSize() );
            auto areaRhs = getArea( rhs.getCollisionRect().getSize() );
            return areaLhs < areaRhs;
        } );

    return collisions.back();
}

void Ball::changeDirection()
{
    auto cs = m_biggestCollision.value().getCollisionRect().getSize();

    if ( isEqual( cs.x, cs.y ) )
    {
        m_velocity.x *= -1;
        m_velocity.y *= -1;
    }
    else if ( cs.x > cs.y )
    {
        m_velocity.y *= -1;
    }
    else
    {
        m_velocity.x *= -1;
    }
}

void Ball::stealLiveFromOneDestructibleObject( const std::vector<Collision>& collisions ) const
{
    std::vector<std::shared_ptr<IDestructible>> desctructibleObjects;
    for ( auto collision : collisions )
    {
        auto desctructible = std::dynamic_pointer_cast<IDestructible>( collision.getObject() );
        if ( desctructible )
        {
            desctructibleObjects.push_back( desctructible );
        }
    }

    if ( !desctructibleObjects.empty() )
    {
        auto& biggestObjectLives = desctructibleObjects.front()->lives();
        if ( biggestObjectLives )
            biggestObjectLives.value()--;
    }
}

void Ball::onBumping( std::vector<Collision>& collisions )
{
    if ( !collisions.empty() )
    {
        m_biggestCollision = getBiggestCollision( collisions );

        if ( m_bonusType && m_bonusType.value() == BonusType::FireBall )
        {
            auto collision = m_biggestCollision.value();
            auto collisionObject = collision.getObject();
            auto desctuctibleObject = std::dynamic_pointer_cast<IDestructible>( collisionObject );
            if ( desctuctibleObject && desctuctibleObject->lives() )
            {
                // do nothing
            }
            else
            {
                changeDirection();
            }
        }
        else
        {
            changeDirection();
        }

        restoreState();
    }
    else
    {
        saveState();
    }

    stealLiveFromOneDestructibleObject( collisions );

    for ( auto collision : collisions )
    {
        std::vector<Collision> oneBackCollision;
        oneBackCollision.emplace_back( shared_from_this(), collision.getCollisionRect() );
        collision.getObject()->onBumping( oneBackCollision );
    }
}

void Ball::calcState( std::optional<sf::Event> event, sf::Time elapsedTime )
{
    if ( m_parent )
        return;

    float sec = elapsedTime.asSeconds();

    float factor = 1.0001f;
    m_velocity *= factor;

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

std::shared_ptr<IObject> Ball::createCopyFromThis()
{
    auto createdObjectPtr = std::make_shared<Ball>();
    Ball& createdObject = *createdObjectPtr.get();
    createdObject = *this;
    return createdObjectPtr;
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
