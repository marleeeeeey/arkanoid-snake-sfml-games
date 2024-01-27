#include "Snake.h"

namespace
{
const auto& snakeColor = getConfig<sf::Color, "game.objects.snake.color">(); // TODO: support default values
}

Snake::Snake()
{
    direction_ = Direction::Right;
}

void Snake::setup( const sf::Vector2u& windowSize )
{
    windowSize_ = windowSize;
    body_.clear();

    auto& segmentSize = getConfig<float, "game.view.cell_size_px">();
    auto& initialNumSegments = getConfig<int, "game.objects.snake.initial_num_segments", 10>();

    sf::RectangleShape segment( sf::Vector2f( segmentSize, segmentSize ) );
    segment.setFillColor( snakeColor );

    for ( int i = 0; i < initialNumSegments; ++i )
    {
        segment.setPosition( windowSize.x / 2, windowSize.y / 2 + i * segmentSize );
        body_.push_back( segment );
    }
}

void Snake::update( const sf::Time& deltaTime )
{
    auto& speed = getConfig<float, "game.objects.snake.speed_pxps", 500>();
    movementValue_ += speed * deltaTime.asSeconds();

    const auto& step = body_.back().getSize().x;

    if ( movementValue_ < step )
        return;

    movementValue_ -= step;

    // Move the rest of the body
    for ( size_t i = body_.size() - 1; i > 0; --i )
        body_[i].setPosition( body_[i - 1].getPosition() );

    // Move the head
    sf::Vector2f movementVector = getNormalizedVectorByDirectionEnum( direction_ ) * step;
    body_.begin()->move( movementVector );
}

void Snake::grow()
{
    assert( !body_.empty() );

    sf::Vector2f movement;
    if ( body_.size() > 1 )
    {
        auto preLastPos = body_[body_.size() - 2].getPosition();
        auto lastPos = body_.back().getPosition();
        movement = lastPos - preLastPos;
    }
    else if ( body_.size() == 1 )
    {
        auto size = body_.back().getSize();
        movement = getNormalizedVectorByDirectionEnum( direction_ ) * size.x;
    }

    sf::RectangleShape newSegment = body_.back();
    newSegment.move( movement );
    body_.push_back( newSegment );
}

void Snake::changeDirection( Direction newDirection )
{
    direction_ = newDirection;
}

void Snake::draw( sf::RenderWindow& window ) const
{
    auto& segmentSpacing = getConfig<float, "game.objects.snake.segment_spacing_px", 5>();

    for ( const auto& segment : body_ )
    {
        auto cropedSegment = segment;
        cropedSegment.setSize( segment.getSize() - sf::Vector2f( segmentSpacing, segmentSpacing ) );
        cropedSegment.move( segmentSpacing / 2, segmentSpacing / 2 );
        window.draw( cropedSegment );
    }
}

bool Snake::collidesWith( const Food& food ) const
{
    return body_.front().getGlobalBounds().intersects( food.getShape().getGlobalBounds() );
}

bool Snake::collidesWithScreenArea() const
{
    if ( body_.empty() )
        return false;

    const sf::RectangleShape& head = body_.front();
    const sf::Vector2f& headPos = head.getPosition();

    if ( headPos.x < 0 || headPos.x + head.getSize().x > windowSize_.x || headPos.y < 0 ||
         headPos.y + head.getSize().y > windowSize_.y )
    {
        return true;
    }

    return false;
}
