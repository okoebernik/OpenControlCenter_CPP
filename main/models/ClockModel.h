#pragma once

#include <cstdint>

namespace OCC
{

class ClockModel
{
public:
    void setSeconds(uint32_t seconds);
    uint32_t seconds() const;

private:
    uint32_t m_seconds = 0;
};

}