#pragma once
#include "DefaultObject.h"
#include "IBonusOwner.h"

class Flier : public DefaultObject, public IBonusOwner
{
    sf::Vector2f m_boundRectStandartSize;
    sf::Vector2f m_boundRectBonusSize;
    std::optional<BonusType> m_bonusType;
    sf::Font m_font;
public:
    Flier();
    void calcState( std::optional<sf::Event> event, sf::Time elapsedTime ) override;
    void draw( sf::RenderWindow& window ) override;
    std::optional<BonusType>& bonusType() override;
    std::shared_ptr<IObject> clone() override;
    std::string name() override;
};
