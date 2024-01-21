#include <gtest/gtest.h>

TEST( UtilsFmtFormat, JsonFormat )
{
    json jsonKey( "A" );
    auto result = fmt::format( "jsonValue={}", jsonKey );
    EXPECT_EQ( result, "jsonValue=\"A\"" );
}
