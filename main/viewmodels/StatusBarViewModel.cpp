#include "StatusBarViewModel.h"

#include <cstdio>

namespace OCC
{

StatusBarViewModel::StatusBarViewModel(ClockModel *clockModel, WiFiModel *wifiModel)
    : m_clockModel(clockModel),
      m_wifiModel(wifiModel)
{
}

void StatusBarViewModel::update()
{
    if (m_clockModel)
    {
        snprintf(
            m_clockText,
            sizeof(m_clockText),
            "%s",
            m_clockModel->timeText()
        );
    }

    if (m_wifiModel)
    {
        snprintf(
            m_wifiText,
            sizeof(m_wifiText),
            "%s",
            m_wifiModel->connected() ? "WiFi OK" : "WiFi -"
        );
    }

    snprintf(
        m_mqttText,
        sizeof(m_mqttText),
        "%s",
        "MQTT -"
    );
}

const char *StatusBarViewModel::clockText() const
{
    return m_clockText;
}

const char *StatusBarViewModel::wifiText() const
{
    return m_wifiText;
}

const char *StatusBarViewModel::mqttText() const
{
    return m_mqttText;
}

}