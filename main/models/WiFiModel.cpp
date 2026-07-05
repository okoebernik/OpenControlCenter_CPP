#include "WiFiModel.h"

#include <cstring>

namespace OCC
{

void WiFiModel::setConnected(bool connected)
{
    m_connected = connected;
}

bool WiFiModel::connected() const
{
    return m_connected;
}

void WiFiModel::setIpText(const char *text)
{
    if (!text)
    {
        return;
    }

    strncpy(m_ipText, text, sizeof(m_ipText));
    m_ipText[sizeof(m_ipText) - 1] = '\0';
}

const char *WiFiModel::ipText() const
{
    return m_ipText;
}

}