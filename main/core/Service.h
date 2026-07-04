#pragma once

#include <cstdint>

namespace OCC
{

class Service
{
public:
    virtual ~Service() = default;

    virtual void begin() {}
    virtual void update(uint32_t deltaMs) {}
};

}