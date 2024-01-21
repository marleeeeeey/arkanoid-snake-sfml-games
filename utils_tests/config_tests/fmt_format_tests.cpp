#include <gtest/gtest.h>

TEST( UtilsFmtFormat, FmtJson )
{
    json jsonKey( "A" );
    auto result = fmt::format( "jsonValue={}", jsonKey );
    EXPECT_EQ( result, "jsonValue=\"A\"" );
}

TEST( UtilsFmtFormat, FmtSfVector2 )
{
    sf::Vector2i expextedPoint{ 100, 200 };
    auto resultFmt = fmt::format( "point={}", expextedPoint );
    EXPECT_EQ( resultFmt, R"(point={"x":100,"y":200})" );
}