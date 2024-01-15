#pragma once
#include <fmt/format.h>
#include <SFML/System/Vector2.hpp>

template <typename T>
struct fmt::formatter<sf::Vector2<T>> : formatter<std::string_view>
{
    template <typename FormatContext>
    auto format( const sf::Vector2<T>& vector, FormatContext& ctx )
    {
        return fmt::format_to( ctx.out(), "({}, {})", vector.x, vector.y );
    }
}; // namespace fmt
