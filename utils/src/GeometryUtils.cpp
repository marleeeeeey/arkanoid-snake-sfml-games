#include <utils/GeometryUtils.h>

namespace
{

void setOriginPointInCenter( sf::Shape& shape )
{
    auto localBound = shape.getLocalBounds();
    auto thickness = shape.getOutlineThickness();
    shape.setOrigin( { localBound.width / 2 - thickness, localBound.height / 2 - thickness } );
}

} // namespace

sf::RectangleShape createRectangleShape( sf::Vector2f size, sf::Vector2f pos, bool isCenter )
{
    sf::RectangleShape shape( size );
    shape.setPosition( pos );
    shape.setFillColor( sf::Color::Transparent );
    shape.setOutlineColor( sf::Color::White );
    shape.setOutlineThickness( 2 );
    if ( !isCenter )
    {
        shape.move( { size.x / 2, size.y / 2 } );
    }
    setOriginPointInCenter( shape );
    return shape;
}

sf::RectangleShape createRectangleShape( const sf::FloatRect& rect )
{
    return createRectangleShape( { rect.width, rect.height }, { rect.left, rect.top }, false );
}

sf::CircleShape createCircleShape( const float radius, const sf::Vector2f pos )
{
    sf::CircleShape shape( radius );
    shape.setPosition( pos );
    shape.setFillColor( sf::Color::Transparent );
    shape.setOutlineColor( sf::Color::White );
    shape.setOutlineThickness( 2 );
    setOriginPointInCenter( shape );
    return shape;
}

sf::RectangleShape extractInsideRectShape( const sf::CircleShape& circleShape )
{
    float insideRectSize = std::cos( 45.0f ) * circleShape.getRadius() * 2.0f;
    sf::RectangleShape rectShape =
        createRectangleShape( { insideRectSize, insideRectSize }, circleShape.getPosition() );
    setOriginPointInCenter( rectShape );
    return rectShape;
}

std::optional<sf::FloatRect> getIntersectRect( const sf::Shape& shape1, const sf::Shape& shape2 )
{
    const auto& insideRect = shape1.getGlobalBounds();
    const auto& rect = shape2.getGlobalBounds();
    sf::FloatRect outFloatRect;
    auto isIntersect = insideRect.intersects( rect, outFloatRect );
    if ( isIntersect )
        return outFloatRect;

    return {};
}

std::optional<sf::RectangleShape> getIntersectRectShape( const sf::Shape& shape1, const sf::Shape& shape2 )
{
    auto instersectRect = getIntersectRect( shape1, shape2 );

    if ( instersectRect )
    {
        auto rectShape = createRectangleShape( instersectRect.value() );
        rectShape.setOutlineThickness( 0 );
        rectShape.setFillColor( sf::Color( 100, 100, 100, 200 ) );
        return rectShape;
    }

    return {};
}

bool isIntersect( const sf::Shape& shape1, const sf::Shape& shape2 )
{
    return getIntersectRect( shape1, shape2 ).has_value();
}

sf::Color getAlphaColor( sf::Color color, sf::Uint8 alpha )
{
    color.a = alpha;
    return color;
}

void setTextCenterTo( sf::Text& text, sf::Vector2f centerPos )
{
    text.setPosition( centerPos );
    auto textRect = createRectangleShape( text.getGlobalBounds() );
    auto t = textRect.getPosition();
    auto c = centerPos;
    sf::Vector2f diff = { t.x - c.x, t.y - c.y };

    text.move( -diff );
}
