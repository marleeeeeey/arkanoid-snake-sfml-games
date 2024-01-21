#include <gtest/gtest.h>
#include <utils/Config.h>

TEST( StringLiteral, Basics )
{
    auto stringView = toStringView<"literal string">();
    ASSERT_EQ( stringView, "literal string" );
}

TEST( UtilsConfig, ReadIntValue )
{
    Config::getInstance( Config::Mode::ForceReload, R"( { "intValue": 123 } )" );

    auto intValue = getConfig<int, "intValue">();
    ASSERT_EQ( intValue, 123 );
}

TEST( UtilsConfig, ReadDefaultValues )
{
    Config::getInstance( Config::Mode::ForceReload, R"( { "hello": 123 } )" );

    auto noExistingValue = getConfig<int, "noExistingValue", 456>();
    ASSERT_EQ( noExistingValue, 456 );
}

TEST( UtilsConfig, ReadFloatValue )
{
    Config::getInstance( Config::Mode::ForceReload, R"( { "floatValue": 123.5 } )" );

    auto floatValue = getConfig<float, "floatValue", 600>();
    ASSERT_EQ( floatValue, 123.5 );
}
