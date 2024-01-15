#include "MathVector.h"
#include "HelperFunctions.h"

float radToDeg( float radians )
{
    auto degrees = radians * ( 180.0f / std::numbers::pi_v<float> );
    return degrees;
}

float degToRad( float degrees )
{
    auto radians = degrees / ( 180.0f / std::numbers::pi_v<float> );
    return radians;
}

MathVector::MathVector()
{
    setSize( 0 );
    setAngle( 0 );
}

MathVector::MathVector( float angleDeg, float size )
{
    setSize( size );
    setAngle( angleDeg );
}

MathVector::MathVector( sf::Vector2f coordinates )
{
    setCoordinates( coordinates );
}

MathVector& MathVector::operator=( sf::Vector2f coordinates )
{
    setCoordinates( coordinates );
    return *this;
}

void MathVector::setSize( float size )
{
    m_size = size;
}

float MathVector::getSize() const
{
    return m_size;
}

void MathVector::setAngle( float angleDeg )
{
    while ( angleDeg >= 360.0f )
    {
        angleDeg -= 360.0f;
    }
    while ( angleDeg < 0.0f )
    {
        angleDeg += 360.0f;
    }
    m_angle_deg = angleDeg;
}

float MathVector::getAngle() const
{
    return m_angle_deg;
}

void MathVector::setCoordinates( sf::Vector2f coordinate )
{
    auto x = coordinate.x;
    auto y = coordinate.y;
    setSize( sqrt( x * x + y * y ) );

    if ( hf::isEqual( x, 0.0f ) )
    {
        if ( hf::isEqual( y, 0.0f ) )
            setAngle( 0 );
        else if ( y > 0 )
            setAngle( 90 );
        else
            setAngle( -90 );
    }
    else if ( hf::isEqual( y, 0.0f ) )
    {
        if ( hf::isEqual( x, 0.0f ) )
            setAngle( 0 );
        if ( x > 0 )
            setAngle( 0 );
        else
            setAngle( 180 );
    }
    else
    {
        auto radians = std::atan( std::abs( y ) / std::abs( x ) );
        auto deg = radToDeg( radians );
        if ( x > 0 && y > 0 )
            setAngle( deg );
        else if ( x > 0 && y < 0 )
            setAngle( -deg );
        else if ( x < 0 && y > 0 )
            setAngle( 180 - deg );
        else if ( x < 0 && y < 0 )
            setAngle( 180 + deg );
        else
            throw std::runtime_error( "MathVector::setCoordinates angle error" );
    }
}

sf::Vector2f MathVector::getCoordinate() const
{
    auto radians = degToRad( m_angle_deg );
    sf::Vector2f coord;
    coord.y = sin( radians ) * m_size;
    coord.x = cos( radians ) * m_size;
    return coord;
}

void MathVector::rotate( float angleDeg )
{
    setAngle( getAngle() + angleDeg );
}

void MathVector::reflectFromVertical()
{
    auto coordinate = getCoordinate();
    coordinate.x = -coordinate.x;
    setCoordinates( coordinate );
}

void MathVector::reflectFromHorizontal()
{
    auto coordinate = getCoordinate();
    coordinate.y = -coordinate.y;
    setCoordinates( coordinate );
}
