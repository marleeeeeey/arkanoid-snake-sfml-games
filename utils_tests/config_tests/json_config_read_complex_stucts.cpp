#include <gtest/gtest.h>
#include <utils/Config.h>

TEST( UtilsConfigReadComplexStructs, ReadSfVector2 )
{
    Config::getInstance( Config::Mode::ForceReload, R"( { "point": { "x": 100, "y" : 200 } } )" );

    auto readPoint = getConfig<sf::Vector2i, "point">();
    sf::Vector2i expextedPoint{ 100, 200 };
    EXPECT_EQ( readPoint, expextedPoint );
}

TEST( UtilsConfigReadComplexStructs, FmtSfVector2 )
{
    Config::getInstance( Config::Mode::ForceReload, R"( { "point": { "x": 100, "y" : 200 } } )" );

    auto readPoint = getConfig<sf::Vector2i, "point">();
    auto resultFmt = fmt::format( "point={}", readPoint );
    EXPECT_EQ( resultFmt, "point={\"x\":100,\"y\":200}" );
}