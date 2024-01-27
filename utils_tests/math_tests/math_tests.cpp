#include <gtest/gtest.h>

TEST( Math, RoundStep )
{
    EXPECT_EQ( roundStep( 85, 10 ), 80 );
    EXPECT_EQ( roundStep( 86, 10 ), 80 );
    EXPECT_EQ( roundStep( 0, 10 ), 0 );
    EXPECT_EQ( roundStep( 100, 10 ), 100 );
}
