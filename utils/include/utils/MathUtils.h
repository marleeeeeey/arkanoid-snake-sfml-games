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