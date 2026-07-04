#include "ClockModel.h"

namespace OCC
{

void ClockModel::setSeconds(uint32_t seconds)
{
    m_seconds = seconds;
}

uint32_t ClockModel::seconds() const
{
    return m_seconds;
}

}