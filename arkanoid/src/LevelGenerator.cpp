#include "LevelGenerator.h"
#include "IDestructible.h"
#include "IBonusOwner.h"

std::vector<Level> LevelGenerator::getSymbolLevels()
{
    std::vector<Level> standartLevels{
        {
            "...............................",
            ".1....1111.1..1.1111.1....1111.",
            ".1....1....1..1.1....1....1....",
            ".1....1111.1..1.1111.1....1111.",
            ".1....1....1..1.1....1.......1.",
            ".1111.1111..11..1111.1111.1111.",
            "...............................",
            ".1111.1111.1111.1111.1111.1111.",
            ".1....1.11.1.11.1..1.1.11.1....",
            ".1111.11...11...1..1.11...1111.",
            ".1....1.1..1.1..1..1.1.1.....1.",
            ".1111.1..1.1..1.1111.1..1.1111.",
            "...............................",
            "....MMMM.LLLL.RRR.DDDD.MMMMM...",
            "...............................",
        },
    };

    checkLevels( standartLevels );

    if ( loadedLevels.empty() )
    {
        MY_LOG_FMT( warn, "No levels loaded, using standart levels" );
        return standartLevels;
    }

    MY_LOG_FMT( info, "Loaded {} levels", loadedLevels.size() );
    return loadedLevels;
}

void LevelGenerator::readLevelsFromTextFile()
{
    auto configPath = getFullPath( "config\\config.txt" );
    std::ifstream infile( configPath );

    MY_LOG_FMT( info, "Config file loaded: {}", configPath.string() );

    loadedLevels.clear();
    std::string line;
    Level level;
    while ( std::getline( infile, line ) )
    {
        trim( line );
        if ( line.empty() )
        {
            if ( !level.empty() )
            {
                loadedLevels.push_back( level );
                level.clear();
            }
            continue;
        }
        level.push_back( line );
    }

    if ( !level.empty() )
    {
        loadedLevels.push_back( level );
    }
}

void LevelGenerator::everyLevelLinesHasTheSameLength( const std::vector<Level>& levels )
{
    for ( const auto& level : levels )
    {
        if ( level.empty() )
            throw std::logic_error( "level is empty" );

        auto lineSize = level.front().size();
        for ( const auto& line : level )
        {
            if ( lineSize != line.size() )
                throw std::logic_error( "level contains lines with different length" );
        }
    }
}

void LevelGenerator::levelsHaveCorrectBonusLetters( const std::vector<Level>& levels )
{
    for ( const auto& level : levels )
    {
        for ( const auto& line : level )
        {
            for ( auto ch : line )
            {
                if ( isalpha( ch ) )
                    getBonusTypeFromChar( ch );
            }
        }
    }
}

void LevelGenerator::checkLevels( const std::vector<Level>& levels )
{
    everyLevelLinesHasTheSameLength( levels );
    levelsHaveCorrectBonusLetters( levels );
}

LevelGenerator::LevelGenerator( std::shared_ptr<IObjectFactory> objectFactory, sf::Vector2f worldSize )
{
    try
    {
        readLevelsFromTextFile();
        checkLevels( loadedLevels );
    }
    catch ( const std::exception& e )
    {
        loadedLevels.clear();
        MY_LOG( warn, e.what() );
    }

    m_objectFactory = std::move( objectFactory );
    m_worldSize = worldSize;
    float wide = 0.95f;
    m_brickZoneSize = { m_worldSize.x * wide, m_worldSize.y * 0.6f };
    m_brickZoneLeftTopPos = { m_worldSize.x * ( 1 - wide ) / 2, m_worldSize.y * 0.1f };
    m_brickGap = 5;
    m_levels = getSymbolLevels();
    m_randomLevelNumbers = NoRepeatableRandoms<size_t>( m_levels.size(), 0, m_levels.size() - 1 );
    // m_randomLevelNumbers.sort(); // TODO: uncomment this line to make levels random
}

void LevelGenerator::setNextLevel()
{
    m_currentLevelNumber = m_randomLevelNumbers.pull();
    MY_LOG_FMT( info, "Level changed to {}/{}", m_currentLevelNumber + 1, m_levels.size() );
}

std::vector<std::shared_ptr<IObject>> LevelGenerator::getLevelBricks()
{
    setNextLevel();
    auto levelNumber = m_currentLevelNumber % m_levels.size();
    auto currentLevel = m_levels.at( levelNumber );
    sf::Vector2<size_t> resolutionInBricks;
    resolutionInBricks.x = currentLevel.front().size();
    resolutionInBricks.y = currentLevel.size();
    std::vector<std::shared_ptr<IObject>> bricks;
    sf::Vector2f brickSize = { m_brickZoneSize.x / resolutionInBricks.x, m_brickZoneSize.y / resolutionInBricks.y };
    for ( size_t brickCol = 0; brickCol < resolutionInBricks.x; ++brickCol )
    {
        for ( size_t brickRow = 0; brickRow < resolutionInBricks.y; ++brickRow )
        {
            char symbol = currentLevel[brickRow][brickCol];
            if ( symbol == '.' )
                continue;
            auto obj = m_objectFactory->createObject( ObjectType::Brick );
            sf::Vector2f brickPos = {
                brickSize.x / 2 + brickCol * brickSize.x + m_brickZoneLeftTopPos.x,
                brickSize.y / 2 + brickRow * brickSize.y + m_brickZoneLeftTopPos.y };
            obj->state().setPos( brickPos );
            obj->state().setSize( { brickSize.x - m_brickGap, brickSize.y - m_brickGap } );
            auto brick = std::dynamic_pointer_cast<IDestructible>( obj );
            auto bonus = std::dynamic_pointer_cast<IBonusOwner>( obj );
            if ( std::isdigit( symbol ) )
            {
                int number = fromChar<int>( symbol );
                if ( number == 0 )
                    brick->lives() = {};
                else
                    brick->lives() = number;
                bonus->bonusType() = {};
            }
            else
            {
                brick->lives() = 1;
                bonus->bonusType() = getBonusTypeFromChar( symbol );
            }
            bricks.push_back( obj );
        }
    }

    return bricks;
}
