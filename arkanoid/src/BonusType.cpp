#include "BonusType.h"

namespace
{

const std::map<BonusType, char>& getBonusMap()
{
    static const std::map<BonusType, char> bonusMap = {
        { BonusType::RenewableBalls, 'R' }, { BonusType::MultiBalls, 'M' },   { BonusType::AddPlateLive, 'A' },
        { BonusType::LongPlate, 'L' },      { BonusType::MagnetPaddle, 'G' }, { BonusType::DisableBonuses, 'D' },
        { BonusType::AroundWall, 'W' },     { BonusType::NextLevel, 'N' },    { BonusType::DecreaseBallSpeed, 'S' },
        { BonusType::FireBall, 'F' },
    };

    return bonusMap;
}

} // namespace

BonusType getBonusTypeFromInt( int number )
{
    int size = static_cast<int>( BonusType::FireBall ) + 1;
    int bonusNum = number % size;
    return static_cast<BonusType>( bonusNum );
}

BonusType getBonusTypeFromChar( char ch )
{
    auto foundIt = std::ranges::find_if( getBonusMap(), [ch]( const auto& pair ) { return pair.second == ch; } );
    if ( foundIt != getBonusMap().end() )
        return foundIt->first;

    throw std::runtime_error( MY_FMT( "Can't convert char '{}` to BonusType", ch ) );
}

std::ostream& operator<<( std::ostream& os, const BonusType& type )
{
    os << getBonusMap().at( type );
    return os;
}
