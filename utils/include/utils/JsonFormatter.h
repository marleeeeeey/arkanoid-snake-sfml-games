// ReSharper disable CppInconsistentNaming
#pragma once
#include <fmt/format.h>
#include <utils/JsonFormatterUserDefined.h>

struct adl_serializer
{
    // Convert any enum to json
    template <typename T>
        requires requires( T enumValue ) { magic_enum::enum_name( enumValue ); }
    static void to_json( json& j, const T& enumValue )
    {
        j = magic_enum::enum_name( enumValue );
    }

    // Convert any enum from json
    template <typename T>
        requires requires( T ) { magic_enum::enum_cast<T>( std::declval<json&>().get<std::string>() ).value(); }
    static void from_json( const json& j, T& enumValue )
    {
        enumValue = magic_enum::enum_cast<sf::Keyboard::Key>( j.get<std::string>() ).value();
    }
};

// Format any json
template <>
struct fmt::formatter<nlohmann::json> : fmt::formatter<std::string>
{
    template <typename FormatContext>
    auto format( const nlohmann::json& j, FormatContext& ctx )
    {
        std::string jsonStr = j.dump();
        return fmt::format_to( ctx.out(), "{}", jsonStr );
    }
};

// Format types that have json serialization
template <typename T>
    requires requires( T key ) { adl_serializer::to_json( std::declval<json&>(), key ); }
struct fmt::formatter<T> : fmt::formatter<std::string_view>
{
    template <typename FormatContext>
    auto format( const T& key, FormatContext& ctx )
    {
        json jsonKey;
        adl_serializer::to_json( jsonKey, key );
        return fmt::format_to( ctx.out(), "{}", jsonKey );
    }
};
