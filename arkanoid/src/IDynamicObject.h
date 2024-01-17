#pragma once

class IDynamicObject
{
public:
    virtual ~IDynamicObject() = default;
    virtual glm::vec2& velocity() = 0;
};
