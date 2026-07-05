#include "ClockModel.h"

#include <cstring>

namespace OCC
{

void ClockModel::setTimeText(const char *text)
{
    if (!text)
    {
        return;
    }

    strncpy(m_timeText, text, sizeof(m_timeText));
    m_timeText[sizeof(m_timeText) - 1] = '\0';
}

const char *ClockModel::timeText() const
{
    return m_timeText;
}

}