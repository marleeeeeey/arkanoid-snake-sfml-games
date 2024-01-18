#pragma once

inline int randomInt( int min, int max )
{
    assert( max - min >= 0 );
    static std::random_device rd;
    static std::mt19937 gen( rd() );
    std::uniform_int_distribution distribution( min, max );
    int randomNumber = distribution( gen );
    return randomNumber;
}

template <typename T>
bool isEqual( T lhs, T rhs, T eps = 0.0001f )
{
    return std::fabs( lhs - rhs ) < eps;
}

inline bool randomBool()
{
    return randomInt( 0, 1 ) == 1;
}