#pragma once

// TODO: improve it
// 1. Store two vectors?
// 2. Improve operations with vectors
class MathVector
{
    float m_size{};
    float m_angle_deg{};
public:
    explicit MathVector();
    explicit MathVector( float angleDeg, float size );
    explicit MathVector( sf::Vector2f coordinates );
    MathVector& operator=( sf::Vector2f coordinates );

    void setSize( float size );
    [[nodiscard]] float getSize() const;

    void setAngle( float angleDeg );
    [[nodiscard]] float getAngle() const;

    void setCoordinates( sf::Vector2f coordinate );
    [[nodiscard]] sf::Vector2f getCoordinate() const;

    void rotate( float angleDeg );
    void reflectFromVertical();
    void reflectFromHorizontal();
};
