#pragma once
#include <optional>
#include <sstream>

namespace HelperFunctions
{
bool isKeyPressed( sf::Event event, sf::Keyboard::Key key );

sf::Font getDefaultFont();

sf::RectangleShape createRectangleShape( sf::Vector2f size, sf::Vector2f pos, bool isCenter = true );
sf::RectangleShape createRectangleShape( const sf::FloatRect& rect );
sf::CircleShape createCircleShape( float radius, sf::Vector2f pos );
void setTextCenterTo( sf::Text& text, sf::Vector2f centerPos );

sf::RectangleShape extractInsideRectShape( const sf::CircleShape& circleShape );
std::optional<sf::FloatRect> getIntersectRect( const sf::Shape& shape1, const sf::Shape& shape2 );
std::optional<sf::RectangleShape> getIntersectRectShape( const sf::Shape& shape1, const sf::Shape& shape2 );
bool isIntersect( const sf::Shape& shape1, const sf::Shape& shape2 );

sf::Color getAlphaColor( sf::Color color, sf::Uint8 alpha );

template <typename T>
std::string toString( const T& value )
{
    std::ostringstream ss;
    ss << value;
    return ss.str();
}

template <typename T>
bool isEqual( T lhs, T rhs, T eps = 0.01f )
{
    return std::fabs( lhs - rhs ) < eps;
}

int charToInt( char ch );

int randomInt( int min, int max );

// trim from start (in place)
inline void ltrim( std::string& s )
{
    s.erase( s.begin(), std::ranges::find_if( s, []( int ch ) { return !std::isspace( ch ); } ) );
}

// trim from end (in place)
inline void rtrim( std::string& s )
{
    s.erase( std::find_if( s.rbegin(), s.rend(), []( int ch ) { return !std::isspace( ch ); } ).base(), s.end() );
}

// trim from both ends (in place)
inline void trim( std::string& s )
{
    ltrim( s );
    rtrim( s );
}

// trim from start (copying)
inline std::string ltrimCopy( std::string s )
{
    ltrim( s );
    return s;
}

// trim from end (copying)
inline std::string rtrimCopy( std::string s )
{
    rtrim( s );
    return s;
}

// trim from both ends (copying)
inline std::string trimCopy( std::string s )
{
    trim( s );
    return s;
}
} // namespace HelperFunctions

namespace hf = HelperFunctions;
