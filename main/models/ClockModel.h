#pragma once

namespace OCC
{

class ClockModel
{
public:
    void setTimeText(const char *text);
    const char *timeText() const;

private:
    char m_timeText[16] = "00:00";
};

}