// ReSharper disable CppInconsistentNaming
#pragma once

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
        enumValue = magic_enum::enum_cast<T>( j.get<std::string>() ).value();
    }

    // ***************************************************************
    // ***************************************************************
    // ***************************************************************

    // Option 1: Add to_json/from_json to adl_serializer.
    // In this place define cutom rules to serialize/deserialize to json.
    // These rules will be also used for fmt::format.

    // Option 2: Use NLOHMANN_DEFINE_TYPE_INTRUSIVE inside your own class/struct.
    // Example:
    // struct Address
    // {
    //     std::string street;
    //     int housenumber{};
    //     int postcode{};
    //     auto operator<=>( const Address& ) const = default;
    //     NLOHMANN_DEFINE_TYPE_INTRUSIVE( Address, street, housenumber, postcode )
    // };

    // ***************************************************************

    template <typename T>
    static void to_json( json& j, const sf::Vector2<T>& data )
    {
        j = json{ { "x", data.x }, { "y", data.y } };
    }

    template <typename T>
    static void from_json( const json& j, sf::Vector2<T>& data )
    {
        data.x = j.at( "x" ).get<T>();
        data.y = j.at( "y" ).get<T>();
    }

    // ***************************************************************
    // ***************************************************************
    // ***************************************************************
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
