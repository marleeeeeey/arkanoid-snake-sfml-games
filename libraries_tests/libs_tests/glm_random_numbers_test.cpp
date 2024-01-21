#include <gtest/gtest.h>

TEST( GlmTests, RandomNumberBounds )
{
    EXPECT_EQ( glm::linearRand( 100, 200 ) > 100, true );
    EXPECT_EQ( glm::linearRand( 100, 200 ) < 200, true );
    EXPECT_EQ( glm::linearRand( 100.05, 100.10 ) > 100.05, true );
    EXPECT_EQ( glm::linearRand( 100.05, 100.10 ) < 100.10, true );
}

TEST( GlmTests, RandomNumberUniqueness )
{
    for ( int i = 0; i < 5; ++i )
    {
        MY_LOG_FMT( info, "{}", glm::linearRand( 100.1, 100.2 ) );
    }
}