#include "SettingsModel.h"

#include <cstring>

namespace OCC
{

void SettingsModel::setHostname(const char *hostname)
{
    if (!hostname) return;

    strncpy(m_hostname, hostname, sizeof(m_hostname));
    m_hostname[sizeof(m_hostname) - 1] = '\0';
}

const char *SettingsModel::hostname() const
{
    return m_hostname;
}

void SettingsModel::setMqttBroker(const char *broker)
{
    if (!broker) return;

    strncpy(m_mqttBroker, broker, sizeof(m_mqttBroker));
    m_mqttBroker[sizeof(m_mqttBroker) - 1] = '\0';
}

const char *SettingsModel::mqttBroker() const
{
    return m_mqttBroker;
}

void SettingsModel::setDisplayBrightness(int brightness)
{
    if (brightness < 0) brightness = 0;
    if (brightness > 100) brightness = 100;

    m_displayBrightness = brightness;
}

int SettingsModel::displayBrightness() const
{
    return m_displayBrightness;
}

}