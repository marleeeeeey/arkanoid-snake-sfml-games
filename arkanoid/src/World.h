#pragma once
#include "IObjectFactory.h"
#include "IWorld.h"
#include "CollisionBucket.h"
#include "ILevelGenerator.h"

class World : public IWorld
{
    std::shared_ptr<IObjectFactory> m_objectFactory;
    std::shared_ptr<ILevelGenerator> m_levelGenerator;
    sf::Vector2f m_windowSize;
    std::vector<std::shared_ptr<IObject>> m_balls;
    std::vector<std::shared_ptr<IObject>> m_plates;
    std::vector<std::shared_ptr<IObject>> m_bricks;
    std::vector<std::shared_ptr<IObject>> m_walls;
    std::vector<std::shared_ptr<IObject>> m_bonuses;
    std::vector<CollisionBucket> m_collisionBuckets;
    sf::Font m_font;
    unsigned m_scopes;
    bool m_isGameOver;
    int m_elapsedTime_ms{};
    std::shared_ptr<IObject> m_pauseMenu;

    std::vector<std::shared_ptr<IObject>> getAllObjects();
    bool isObjectOutOfBorder( const std::shared_ptr<IObject>& object ) const;
    static void removeObjectsIfDestroyed( std::vector<std::shared_ptr<IObject>>& objects );
    void removeAllDestroyedObjects();
    void removeAllObjects();
    void generate();
    void updateGameOverStatus();
    void onEveryUpdate();
    void initPlates();
    void initWalls();
    void initBricks();
    void initBalls();
    void initCollisionProcessors();
    std::vector<std::shared_ptr<IObject>> generateNewBalls( size_t ballsNumber ) const;
public:
    World(
        const std::shared_ptr<IObjectFactory>& objectFactory, std::shared_ptr<ILevelGenerator> levelGenerator,
        sf::Vector2f windowSize );
    void updateState( std::optional<sf::Event> event, sf::Time elapsedTime ) override;
    void draw( sf::RenderWindow& window ) override;
};
