#include "Bonus.h"

Bonus::Bonus()
{
    m_font = getDefaultFont();
    m_boundRectStandartSize = { 5, 5 };
    m_boundRectBonusSize = { 20, 20 };
}

void Bonus::calcState( [[maybe_unused]] std::optional<sf::Event> event, sf::Time elapsedTime )
{
    sf::Vector2f speed = { 0, 100 };

    auto pos = state().getPos();
    sf::Vector2f offset = { elapsedTime.asSeconds() * speed.x, elapsedTime.asSeconds() * speed.y };
    state().setPos( pos + offset );
    if ( m_bonusType )
    {
        state().setSize( m_boundRectBonusSize );
    }
    else
    {
        state().setSize( m_boundRectStandartSize );
    }
}

void Bonus::draw( sf::RenderWindow& window )
{
    auto shape = state().getCollisionRect();
    shape.setFillColor( getAlphaColor( sf::Color::Yellow, 0x80 ) );

    if ( m_bonusType )
    {
        sf::Text text;
        text.setFont( m_font );
        text.setFillColor( sf::Color::Black );
        text.setString( toString( m_bonusType.value() ) );
        setTextCenterTo( text, state().getPos() );
        window.draw( shape );
        window.draw( text );
    }
    else
    {
        window.draw( shape );
    }
}

std::optional<BonusType>& Bonus::bonusType()
{
    return m_bonusType;
}

std::shared_ptr<IObject> Bonus::createCopyFromThis()
{
    auto createdObjectPtr = std::make_shared<Bonus>();
    Bonus& createdObject = *createdObjectPtr.get();
    createdObject = *this;
    return createdObjectPtr;
}

std::string Bonus::name()
{
    return "Bonus";
}
