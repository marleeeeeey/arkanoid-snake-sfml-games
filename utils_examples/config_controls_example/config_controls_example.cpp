#include <gtest/gtest.h>
#include <utils/Config.h>

TEST( SfmlKeyboardKey, CheckFmtFormat )
{
    json jsonKey( "A" );
    auto result = fmt::format( "jsonValue={}", jsonKey );
    EXPECT_EQ( result, "jsonValue=\"A\"" );
}

TEST( SfmlKeyboardKey, ReadKeyboardFromConfigManually )
{
    Config::getInstance( Config::Mode::ForceReload, R"( { "controls": { "left": "X" } } )" );
    const auto& left = getConfig<std::string, "controls.left">();
    auto leftKey = magic_enum::enum_cast<sf::Keyboard::Key>( left ).value();
    EXPECT_EQ( leftKey, sf::Keyboard::Key::X );
}

TEST( SfmlKeyboardKey, CheckJsonSerialization )
{
    Config::getInstance( Config::Mode::ForceReload, R"( { "controls": { "left": "X" } } )" );

    auto sfmlKey = sf::Keyboard::Key::W;
    json jsonKey;
    adl_serializer::to_json( jsonKey, sfmlKey );
    EXPECT_EQ( jsonKey, "W" );

    sf::Keyboard::Key sfmlKey2;
    adl_serializer::from_json( jsonKey, sfmlKey2 );
    EXPECT_EQ( sfmlKey2, sf::Keyboard::Key::W );
    EXPECT_EQ( sfmlKey2, sfmlKey );
}

TEST( SfmlKeyboardKey, ReadKeyboardFromConfigAuto )
{
    Config::getInstance( Config::Mode::ForceReload, R"( { "controls": { "left": "X" } } )" );

    const json& leftKey = getConfig<sf::Keyboard::Key, "controls.left">();
    EXPECT_EQ( leftKey, sf::Keyboard::Key::X );
}
