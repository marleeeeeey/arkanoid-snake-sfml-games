#include <gtest/gtest.h>
#include <utils/Config.h>

TEST( StringLiteral, Basics )
{
    auto stringView = toStringView<"literal string">();
    ASSERT_EQ( stringView, "literal string" );
}

TEST( UtilsConfig, ReadValues )
{
    Config::getInstance( Config::Mode::ForceReload, R"( { "hello": 123 } )" );

    auto value = getConfig<int, "hello">();
    ASSERT_EQ( value, 123 );

    auto value2 = getConfig<int, "hello", 456>();
    ASSERT_EQ( value2, 123 );

    auto value3 = getConfig<int, "hello2", 456>();
    ASSERT_EQ( value3, 456 );
}

TEST( UtilsConfig, ReadValuesIntToFloat )
{
    Config::getInstance( Config::Mode::ForceReload, R"( { "hello": 123 } )" );

    auto windowsWidth = getConfig<float, "window.width", 600>();
    ASSERT_EQ( windowsWidth, 600 );
}
