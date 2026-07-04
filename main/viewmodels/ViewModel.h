#pragma once

namespace OCC
{

class ViewModel
{
public:
    virtual ~ViewModel() = default;

    virtual void begin() {}
    virtual void update() {}
};

}