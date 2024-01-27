#pragma once

// ************************************* CREATE SHAPES *******************************************

enum class Anchor
{
    TopLeft,
    Center
};

sf::RectangleShape createRectangleShape( sf::Vector2f size, sf::Vector2f pos, Anchor relativity = Anchor::Center );
sf::RectangleShape createRectangleShape( const sf::FloatRect& rect );
sf::CircleShape createCircleShape( float radius, sf::Vector2f pos );

// ***************************************** OTHER ***********************************************

void updateTextCenter( sf::Text& text, sf::Vector2f centerPos );
sf::RectangleShape extractInsideRectShape( const sf::CircleShape& circleShape );
sf::Color getAlphaColor( sf::Color color, sf::Uint8 alpha );

// **************************************** COLLISION ********************************************

std::optional<sf::FloatRect> calcIntersectRect( const sf::Shape& shape1, const sf::Shape& shape2 );
std::optional<sf::RectangleShape> calcIntersectRectShape( const sf::Shape& shape1, const sf::Shape& shape2 );
bool isIntersect( const sf::Shape& shape1, const sf::Shape& shape2 );

// **************************************** GLM ANGELS ******************************************

[[nodiscard]] glm::vec2 rotateDeg( const glm::vec2& vec, float angleDegrees );
void rotateDegInPlace( glm::vec2& vec, float angleDegrees );
void setAngle( glm::vec2& vec, float angleDegrees );
glm::vec2 vectorFromDirectionAndLength( float angleDegrees, float length );

sf::Vector2f getNormalizedVectorByDirectionEnum( Direction direction );
