#pragma once

namespace OCC
{

class Screen
{
public:
    virtual ~Screen() = default;

    virtual void show() = 0;
    virtual void update() {}
};

}