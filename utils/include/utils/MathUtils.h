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