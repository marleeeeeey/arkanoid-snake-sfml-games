#pragma once

class IMovableObject
{
public:
    virtual ~IMovableObject() = default;
    virtual glm::vec2& velocity() = 0;
};
