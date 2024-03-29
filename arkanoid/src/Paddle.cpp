#include "Paddle.h"
#include "IStaticObject.h"
#include "IMovableObject.h"
#include "IHaveParent.h"
#include "Collision.h"

Paddle::Paddle()
{
    m_velocityDamping = 0;
    m_paddleState = PaddleState::Stop;
}

void Paddle::updateVelocityDamping( std::optional<sf::Event> event, sf::Time elapsedTime )
{
    if ( event && event.value().type == sf::Event::EventType::KeyPressed &&
         event.value().key.code == sf::Keyboard::Key::Left && m_paddleState != PaddleState::MoveLeft )
    {
        m_paddleState = PaddleState::MoveLeft;
    }
    else if (
        event && event.value().type == sf::Event::EventType::KeyReleased &&
        event.value().key.code == sf::Keyboard::Key::Left && m_paddleState == PaddleState::MoveLeft )
    {
        m_paddleState = PaddleState::Stop;
    }
    else if (
        event && event.value().type == sf::Event::EventType::KeyPressed &&
        event.value().key.code == sf::Keyboard::Key::Right && m_paddleState != PaddleState::MoveRight )
    {
        m_paddleState = PaddleState::MoveRight;
    }
    else if (
        event && event.value().type == sf::Event::EventType::KeyReleased &&
        event.value().key.code == sf::Keyboard::Key::Right && m_paddleState == PaddleState::MoveRight )
    {
        m_paddleState = PaddleState::Stop;
    }
    else if (
        event && event.value().type == sf::Event::EventType::KeyReleased &&
        event.value().key.code == sf::Keyboard::Key::Space && m_paddleState != PaddleState::Attack )
    {
        m_paddleState = PaddleState::Attack;
    }

    const auto& speed_pxps = getConfig<float, "game.objects.paddle.speed">();
    float elapsedSec = elapsedTime.asSeconds();
    float absOffset = speed_pxps * elapsedSec;
    const auto& damping = getConfig<float, "game.objects.paddle.damping">();
    float absDampingOffset = absOffset * damping;

    switch ( m_paddleState )
    {
    case PaddleState::Stop:
        m_velocityDamping += -sign( m_velocityDamping ) * absDampingOffset;
        if ( abs( m_velocityDamping ) < absDampingOffset )
            m_velocityDamping = 0;
        break;
    case PaddleState::MoveLeft:
        m_velocityDamping = -absOffset;
        break;
    case PaddleState::MoveRight:
        m_velocityDamping = absOffset;
        break;
    case PaddleState::Attack:
        // TODO implement attack for paddle
        break;
    }
}

void Paddle::calcState( std::optional<sf::Event> event, sf::Time elapsedTime )
{
    // 1. Save initial position
    const sf::Vector2f initialPos = state().getPos();

    // 2. Update velocity damping - uses to smooth stopping
    updateVelocityDamping( event, elapsedTime );

    // 3. Update position by velocity damping
    auto pos = state().getPos();
    pos.x += m_velocityDamping;
    state().setPos( pos );

    // 4. Check and solve collisions
    auto collisions = getCollisions( shared_from_this(), m_collisionWalls );
    auto biggestCollisionOpt = getBiggestCollision( collisions );
    if ( biggestCollisionOpt )
    {
        m_velocityDamping = 0;
        auto biggestCollision = biggestCollisionOpt.value();
        restoreState();
    }
    else
    {
        saveState();
        m_collisionWalls.clear();
    }
    auto posAfterCollisionFixed = state().getPos();

    // 5. Update size if bonus is active
    // TODO: fix collision with wall when paddle is long
    auto size = state().getSize();
    if ( m_bonusType && m_bonusType.value() == BonusType::LongPlate )
    {
        if ( !m_originalSize )
            m_originalSize = size;

        size = m_originalSize.value();
        const auto& longSizeFactor = getConfig<float, "game.objects.paddle.longSizeFactor">();
        size.x *= longSizeFactor;
        state().setSize( size );
    }
    else
    {
        if ( m_originalSize )
            state().setSize( m_originalSize.value() );
    }

    // 6. Update position of magnetized balls with delta position of paddle
    sf::Vector2f deltaPosition = posAfterCollisionFixed - initialPos;
    for ( const auto& ball : m_magnetBalls )
    {
        auto ballPos = ball->state().getPos();
        ballPos += deltaPosition;
        ball->state().setPos( ballPos );
    }
}

void Paddle::draw( sf::RenderWindow& window )
{
    auto shape = state().getCollisionRect();
    shape.setFillColor( sf::Color::Cyan );
    window.draw( shape );

    if ( m_bonusType )
    {
        sf::Text text;
        sf::Font font = getDefaultFont();
        text.setFont( font );
        text.setString( toString( m_bonusType.value() ) );
        text.setFillColor( sf::Color::Blue );
        updateTextCenter( text, state().getPos() );
        window.draw( text );
    }
}

float getShiftCoef( const std::shared_ptr<IObject>& paddle, const std::shared_ptr<IObject>& obj )
{
    auto ballCenter = obj->state().getPos();
    auto paddleCenter = paddle->state().getPos();
    auto centersShift = ballCenter.x - paddleCenter.x;
    auto halfLength = paddle->state().getSize().x / 2;
    auto result = centersShift / halfLength;
    return result;
}

void Paddle::onBumping( std::vector<Collision>& collisions )
{
    for ( auto collision : collisions )
    {
        auto obj = collision.getObject();
        auto wall = std::dynamic_pointer_cast<IStaticObject>( obj );
        auto ball = std::dynamic_pointer_cast<IMovableObject>( obj );
        if ( wall )
        {
            m_collisionWalls.insert( obj );
        }
        if ( ball )
        {
            const auto& angleSensivity = getConfig<float, "game.objects.paddle.angleSensitivity">();
            float angleShift = angleSensivity * getShiftCoef( shared_from_this(), obj );
            rotateDegInPlace( ball->velocity(), angleShift );
            if ( m_bonusType && m_bonusType.value() == BonusType::MagnetPaddle && m_paddleState != PaddleState::Attack )
            {
                auto [_, success] = m_magnetBalls.insert( obj );
                if ( success )
                {
                    auto localBall = std::dynamic_pointer_cast<IHaveParent>( obj );
                    localBall->setParent( shared_from_this() );
                }
            }
            else
            {
                for ( const auto& magnetBall : m_magnetBalls )
                {
                    auto childBall = std::dynamic_pointer_cast<IHaveParent>( magnetBall );
                    childBall->removeParent();
                    // TODO: improve calcualtioan of angle when ball is magnetized
                    float maxAngle_deg = 45;
                    float angle = maxAngle_deg * getShiftCoef( shared_from_this(), magnetBall ) - 90;
                    auto dynamicBall = std::dynamic_pointer_cast<IMovableObject>( magnetBall );
                    setAngle( dynamicBall->velocity(), angle );
                }
                m_magnetBalls.clear();
            }
        }
    }
}

std::optional<BonusType>& Paddle::bonusType()
{
    return m_bonusType;
}

std::shared_ptr<IObject> Paddle::clone()
{
    return std::make_shared<Paddle>( *this );
}

std::string Paddle::name()
{
    return "Paddle";
}
