#pragma once

template <typename T>
bool isEqual( T lhs, T rhs, T eps = 0.0001f )
{
    return std::fabs( lhs - rhs ) < eps;
}

inline bool randomBool()
{
    return glm::linearRand( 0, 1 ) == 1;
}

// Returns 1 if val > 0, -1 if val < 0, and 0 if val == 0.
template <typename T>
T sign( T val )
{
    return ( T( 0 ) < val ) - ( val < T( 0 ) );
}

template <typename T>
T getArea( const sf::Vector2<T>& size )
{
    return size.x * size.y;
}

template <typename T>
sf::Vector2<T> normalize( const sf::Vector2<T>& v )
{
    float length = std::sqrt( v.x * v.x + v.y * v.y );
    if ( length != 0 )
        return sf::Vector2<T>( v.x / length, v.y / length );
    return v;
}

// value = 85, step = 10 => 80
template <typename T>
T roundStep( T value, T step )
{
    return step * glm::round( value / step );
}