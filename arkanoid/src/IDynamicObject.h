#pragma once

class IDynamicObject
{
public:
    virtual ~IDynamicObject() = default;
    virtual MathVector& speed() = 0;
};
