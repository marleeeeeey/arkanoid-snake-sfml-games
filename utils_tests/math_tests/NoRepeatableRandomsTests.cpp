#include <gtest/gtest.h>
#include <set>
#include <limits>

namespace
{
const size_t capacity = 10;
const int min = 0;
const int max = 9;
} // namespace

class NoRepeatableRandomsTest : public ::testing::Test
{
protected:
    NoRepeatableRandoms<int> noRepeatableRandoms;
    NoRepeatableRandomsTest() : noRepeatableRandoms( capacity, min, max ) {}
};

TEST_F( NoRepeatableRandomsTest, InitiallyNotEmpty )
{
    EXPECT_TRUE( !noRepeatableRandoms.empty() );
}

TEST_F( NoRepeatableRandomsTest, PullReducesSize )
{
    for ( size_t i = 0; i < capacity; ++i )
        noRepeatableRandoms.pull();
    EXPECT_TRUE( noRepeatableRandoms.empty() );
}

TEST_F( NoRepeatableRandomsTest, PullReturnsUniqueNumbersInRange )
{
    std::set<int> numbers;
    while ( !noRepeatableRandoms.empty() )
    {
        int num = noRepeatableRandoms.pull();
        EXPECT_GE( num, min );
        EXPECT_LE( num, max );
        numbers.insert( num );
    }

    EXPECT_EQ( numbers.size(), capacity );
}
