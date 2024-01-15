#pragma once
#include <fmt/format.h>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

template <typename T>
struct fmt::formatter<sf::Vector2<T>> : formatter<std::string_view>
{
    template <typename FormatContext>
    auto format( const sf::Vector2<T>& vector, FormatContext& ctx )
    {
        return fmt::format_to( ctx.out(), "({}, {})", vector.x, vector.y );
    }
};

template <>
struct fmt::formatter<sf::Time> : formatter<std::string_view>
{
    template <typename FormatContext>
    auto format( const sf::Time& time, FormatContext& ctx )
    {
        auto milliseconds = time.asMilliseconds();
        return fmt::format_to( ctx.out(), "{} ms", milliseconds );
    }
};

template <>
struct fmt::formatter<sf::Clock> : fmt::formatter<std::string_view>
{
    template <typename FormatContext>
    auto format( const sf::Clock& clock, FormatContext& ctx )
    {
        float timeMilliseconds = clock.getElapsedTime().asMilliseconds();
        return fmt::format_to( ctx.out(), "{} ms", timeMilliseconds );
    }
};