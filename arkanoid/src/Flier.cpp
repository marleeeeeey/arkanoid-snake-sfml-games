#include "Flier.h"

Flier::Flier()
{
    m_font = getDefaultFont();
    m_boundRectStandartSize = { 5, 5 };
    m_boundRectBonusSize = { 20, 20 };
}

void Flier::calcState( [[maybe_unused]] std::optional<sf::Event> event, sf::Time elapsedTime )
{
    sf::Vector2f speed = { 0, getConfig<float, "game.objects.bonus.speed">() * glm::linearRand( 1.0f, 2.0f ) };

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

void Flier::draw( sf::RenderWindow& window )
{
    auto shape = state().getCollisionRect();
    shape.setFillColor( getAlphaColor( sf::Color::Yellow, 0x80 ) );

    if ( m_bonusType )
    {
        sf::Text text;
        text.setFont( m_font );
        text.setFillColor( sf::Color::Black );
        text.setString( toString( m_bonusType.value() ) );
        updateTextCenter( text, state().getPos() );
        window.draw( shape );
        window.draw( text );
    }
    else
    {
        window.draw( shape );
    }
}

std::optional<BonusType>& Flier::bonusType()
{
    return m_bonusType;
}

std::shared_ptr<IObject> Flier::clone()
{
    return std::make_shared<Flier>( *this );
}

std::string Flier::name()
{
    return "Flier";
}
