#include "ObjectFactory.h"
#include "Brick.h"
#include "Ball.h"
#include "Wall.h"
#include "Paddle.h"
#include "Flier.h"

std::shared_ptr<IObject> ObjectFactory::createObject( ObjectType objectType )
{
    switch ( objectType )
    {
    case ObjectType::Brick:
        return std::make_shared<Brick>();
    case ObjectType::Plate:
        return std::make_shared<Paddle>();
    case ObjectType::Ball:
        return std::make_shared<Ball>();
    case ObjectType::Bonus:
        return std::make_shared<Flier>();
    case ObjectType::Wall:
        return std::make_shared<Wall>();
    }
    return {};
}
