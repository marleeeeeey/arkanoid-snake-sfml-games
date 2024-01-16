#pragma once
#include <optional>
#include <SFML/Graphics.hpp>

sf::RectangleShape createRectangleShape( sf::Vector2f size, sf::Vector2f pos, bool isCenter = true );
sf::RectangleShape createRectangleShape( const sf::FloatRect& rect );
sf::CircleShape createCircleShape( float radius, sf::Vector2f pos );
void setTextCenterTo( sf::Text& text, sf::Vector2f centerPos );

sf::RectangleShape extractInsideRectShape( const sf::CircleShape& circleShape );
std::optional<sf::FloatRect> getIntersectRect( const sf::Shape& shape1, const sf::Shape& shape2 );
std::optional<sf::RectangleShape> getIntersectRectShape( const sf::Shape& shape1, const sf::Shape& shape2 );
bool isIntersect( const sf::Shape& shape1, const sf::Shape& shape2 );

sf::Color getAlphaColor( sf::Color color, sf::Uint8 alpha );
