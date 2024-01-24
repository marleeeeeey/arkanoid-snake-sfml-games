#include "World.h"
#include "IBonusOwner.h"
#include "IMovableObject.h"
#include "IDestructible.h"

std::vector<std::shared_ptr<IObject>> World::getAllObjects()
{
    std::vector<std::shared_ptr<IObject>> objects;
    objects.insert( objects.end(), m_balls.begin(), m_balls.end() );
    objects.insert( objects.end(), m_plates.begin(), m_plates.end() );
    objects.insert( objects.end(), m_bricks.begin(), m_bricks.end() );
    objects.insert( objects.end(), m_walls.begin(), m_walls.end() );
    objects.insert( objects.end(), m_bonuses.begin(), m_bonuses.end() );
    return objects;
}

bool World::isObjectOutOfBorder( const std::shared_ptr<IObject>& object ) const
{
    auto objectPos = object->state().getPos();
    if ( objectPos.x < 0 || objectPos.y < 0 || objectPos.x > m_windowSize.x || objectPos.y > m_windowSize.y )
    {
        return true;
    }

    return false;
}

World::World(
    const std::shared_ptr<IObjectFactory>& objectFactory, std::shared_ptr<ILevelGenerator> levelGenerator,
    sf::Vector2f windowSize )
{
    m_objectFactory = objectFactory;
    m_levelGenerator = std::move( levelGenerator );
    m_windowSize = windowSize;
    m_font = getDefaultFont();
    m_isGameOver = true;
    m_scopes = 0;
    m_pauseMenu = objectFactory->createObject( ObjectType::PauseMenu );
    m_pauseMenu->state().setSize( windowSize );
    m_pauseMenu->state().setPos( { windowSize.x / 2, windowSize.y / 2 } );
}

void World::initCollisionProcessors()
{
    m_collisionBuckets.push_back( { m_balls, m_walls, {} } );
    m_collisionBuckets.push_back( { m_balls, m_plates, {} } );
    m_collisionBuckets.emplace_back(
        m_balls, m_bricks,
        [&]( const std::shared_ptr<IObject>& thisObject, const std::vector<Collision>& collisions )
        {
            for ( auto collision : collisions )
            {
                auto brickAsObject = collision.getObject();
                if ( !brickAsObject->state().getDestroyFlag() )
                    continue;
                auto object = m_objectFactory->createObject( ObjectType::Bonus );
                object->state().setPos( thisObject->state().getPos() );
                auto bonus = std::dynamic_pointer_cast<IBonusOwner>( object );
                auto brickAsBonusOwner = std::dynamic_pointer_cast<IBonusOwner>( collision.getObject() );
                bonus->bonusType() = brickAsBonusOwner->bonusType();
                m_bonuses.push_back( object );
            }
        } );
    m_collisionBuckets.push_back( { m_plates, m_walls, {} } );
    m_collisionBuckets.emplace_back(
        m_plates, m_bonuses,
        [&]( const std::shared_ptr<IObject>& thisObject, std::vector<Collision>& collisions )
        {
            for ( auto& collision : collisions )
            {
                auto object = collision.getObject();
                object->state().setDestroyFlag( true );
                auto flier = std::dynamic_pointer_cast<IBonusOwner>( object );
                auto paddle = std::dynamic_pointer_cast<IBonusOwner>( thisObject );
                auto flierBonusType = flier->bonusType();
                if ( flierBonusType )
                    paddle->bonusType() = flierBonusType;

                if ( paddle->bonusType() && paddle->bonusType().value() == BonusType::MultiBalls )
                {
                    int ballsNumber = glm::linearRand( 1, 3 );
                    auto createdBalls = generateNewBalls( ballsNumber );
                    m_balls.insert( m_balls.end(), createdBalls.begin(), createdBalls.end() );
                    auto& maxNumberOfBalls = getConfig<size_t, "game.rules.maxNumberOfBalls">();
                    if ( m_balls.size() > maxNumberOfBalls )
                        m_balls.resize( maxNumberOfBalls );
                }

                if ( paddle->bonusType() && paddle->bonusType().value() == BonusType::DisableBonuses )
                {
                    paddle->bonusType() = {};

                    for ( const auto& ball : m_balls )
                    {
                        auto bonusBall = std::dynamic_pointer_cast<IBonusOwner>( ball );
                        bonusBall->bonusType() = {};
                    }
                }

                if ( paddle->bonusType() && paddle->bonusType().value() == BonusType::FireBall )
                {
                    if ( !m_balls.empty() )
                    {
                        auto firstBall = m_balls.front();
                        auto bonusBall = std::dynamic_pointer_cast<IBonusOwner>( firstBall );
                        bonusBall->bonusType() = paddle->bonusType().value();
                    }
                }

                if ( paddle->bonusType() && paddle->bonusType().value() == BonusType::DecreaseBallSpeed )
                {
                    for ( const auto& ball : m_balls )
                    {
                        auto bonusBall = std::dynamic_pointer_cast<IBonusOwner>( ball );
                        bonusBall->bonusType() = paddle->bonusType().value();
                    }
                }

                m_scopes++;
            }
        } );
}

std::vector<std::shared_ptr<IObject>> World::generateNewBalls( size_t ballsNumber ) const
{
    std::vector<std::shared_ptr<IObject>> createdBalls;
    while ( !m_balls.empty() && createdBalls.size() < ballsNumber )
    {
        for ( const auto& existingBall : m_balls )
        {
            auto createdBall = existingBall->clone();
            auto createdBallDynamicObject = std::dynamic_pointer_cast<IMovableObject>( createdBall );
            auto randomAngle = glm::linearRand<float>( 5, 355 );
            rotateDegInPlace( createdBallDynamicObject->velocity(), randomAngle );
            createdBalls.push_back( createdBall );
            if ( createdBalls.size() == ballsNumber )
                break;
        }
    }
    return createdBalls;
}

void World::initPlates()
{
    float paddleKoefThinkness = 0.025f;
    float paddleKoefSize = 0.2f;
    auto paddle = m_objectFactory->createObject( ObjectType::Plate );
    paddle->state().setSize( { m_windowSize.x * paddleKoefSize, m_windowSize.y * paddleKoefThinkness } );
    paddle->state().setPos( { m_windowSize.x / 2, m_windowSize.y * ( 1 - paddleKoefThinkness ) } );
    paddle->setOnBumpingCallBack( [&]( auto, const std::vector<Collision>& collisions )
                                  { m_scopes += collisions.size(); } );
    m_plates.push_back( paddle );
}

void World::initWalls()
{
    float wallKoefThinkness = 0.02f;
    float wallTopOffset = 0.035f;
    sf::Vector2f verticalWallSize = { m_windowSize.x * wallKoefThinkness, m_windowSize.y * ( 1 - wallTopOffset ) };
    auto leftWall = m_objectFactory->createObject( ObjectType::Wall );
    leftWall->state().setCollisionRect(
        verticalWallSize, { m_windowSize.x * wallKoefThinkness / 2, m_windowSize.y * ( 0.5f + wallTopOffset ) } );
    auto rightWall = m_objectFactory->createObject( ObjectType::Wall );
    rightWall->state().setCollisionRect(
        verticalWallSize,
        { m_windowSize.x * ( 1 - wallKoefThinkness / 2 ), m_windowSize.y * ( 0.5f + wallTopOffset ) } );
    sf::Vector2f horizontalWallSize = { m_windowSize.x, m_windowSize.y * wallKoefThinkness };
    auto topWall = m_objectFactory->createObject( ObjectType::Wall );
    topWall->state().setCollisionRect(
        horizontalWallSize, { m_windowSize.x / 2, m_windowSize.y * ( wallKoefThinkness / 2 + wallTopOffset ) } );
    m_walls.push_back( leftWall );
    m_walls.push_back( rightWall );
    m_walls.push_back( topWall );
}

void World::initBricks()
{
    m_bricks = m_levelGenerator->getLevelBricks();
}

void World::initBalls()
{
    sf::Vector2f ballPos = { m_windowSize.x * 0.5f, m_windowSize.y * 0.9f };
    auto ball = m_objectFactory->createObject( ObjectType::Ball );
    ball->state().setPos( ballPos );
    m_balls.push_back( ball );
}

void World::generate()
{
    m_isGameOver = false;
    removeAllObjects();
    m_collisionBuckets.clear();

    initBalls();
    initBricks();
    initWalls();
    initPlates();
    initCollisionProcessors();
}

void World::removeObjectsIfDestroyed( std::vector<std::shared_ptr<IObject>>& objects )
{
    auto removeIt =
        std::ranges::remove_if( objects, []( auto object ) { return object->state().getDestroyFlag(); } ).begin();

    objects.erase( removeIt, objects.end() );
}

void World::removeAllDestroyedObjects()
{
    removeObjectsIfDestroyed( m_balls );
    removeObjectsIfDestroyed( m_plates );
    removeObjectsIfDestroyed( m_bricks );
    removeObjectsIfDestroyed( m_walls );
    removeObjectsIfDestroyed( m_bonuses );
}

void World::removeAllObjects()
{
    m_balls.clear();
    m_plates.clear();
    m_bricks.clear();
    m_walls.clear();
    m_bonuses.clear();
}

void World::updateGameOverStatus()
{
    auto isAllBallsOutOfBorder =
        std::ranges::none_of( m_balls, [&]( auto ball ) { return !isObjectOutOfBorder( ball ); } );

    auto isAllBricksHaveSuperLive = std::ranges::all_of(
        m_bricks,
        [&]( auto brick )
        {
            auto destructibleBall = std::dynamic_pointer_cast<IDestructible>( brick );
            std::optional<int> lives = destructibleBall->lives();
            return !lives.has_value();
        } );

    if ( m_bricks.empty() || isAllBricksHaveSuperLive )
    {
        std::ranges::for_each(
            m_balls, []( const std::shared_ptr<IObject>& ballObject ) { ballObject->state().setDestroyFlag( true ); } );

        if ( m_bonuses.empty() )
        {
            m_isGameOver = true;
            m_levelGenerator->changeLevel();
        }
    }
    else if ( isAllBallsOutOfBorder && !m_bricks.empty() )
    {
        m_scopes = 0;
        m_isGameOver = true;
    }
}

void World::onEveryUpdate()
{
    if ( m_plates.empty() )
        return;

    auto paddle = std::dynamic_pointer_cast<IBonusOwner>( m_plates.front() );
    auto paddleBonus = paddle->bonusType();
    if ( paddleBonus && paddleBonus.value() == BonusType::RenewableBalls )
    {
        size_t countRenewableBalls = 3;
        if ( m_balls.size() < countRenewableBalls )
        {
            auto ballsNumber = countRenewableBalls - m_balls.size();
            auto createdBalls = generateNewBalls( ballsNumber );
            m_balls.insert( m_balls.end(), createdBalls.begin(), createdBalls.end() );
        }
    }
}

void World::updateState( std::optional<sf::Event> event, sf::Time elapsedTime )
{
    m_elapsedTime_ms = elapsedTime.asMilliseconds();

    m_pauseMenu->calcState( event, elapsedTime );

    if ( m_pauseMenu->isVisible() )
    {
        return;
    }

    if ( m_isGameOver )
    {
        generate();
    }

    onEveryUpdate();

    for ( auto& collisionProcessor : m_collisionBuckets )
    {
        collisionProcessor.process();
    }
    removeAllDestroyedObjects();

    for ( const auto& object : getAllObjects() )
    {
        object->calcState( event, elapsedTime );
        if ( isObjectOutOfBorder( object ) )
        {
            object->state().setDestroyFlag( true );
        }
    }
    removeAllDestroyedObjects();

    updateGameOverStatus();
}

void World::draw( sf::RenderWindow& window )
{
    for ( const auto& object : getAllObjects() )
    {
        object->draw( window );
    }

    sf::Text text;
    text.setFont( m_font );
    text.setScale( 0.7f, 0.7f );

    auto fps = m_elapsedTime_ms ? 1000 / m_elapsedTime_ms : 0;
    std::string info = fmt::format( "Scopes: {} Ball count: {} FPS: {}", m_scopes, m_balls.size(), fps );

    text.setString( info );
    window.draw( text );

    if ( m_pauseMenu->isVisible() )
    {
        m_pauseMenu->draw( window );
    }
}
