#pragma once

namespace OCC
{

class SettingsModel
{
public:
    void setHostname(const char *hostname);
    const char *hostname() const;

    void setMqttBroker(const char *broker);
    const char *mqttBroker() const;

    void setDisplayBrightness(int brightness);
    int displayBrightness() const;

private:
    char m_hostname[32] = "occ-panel";
    char m_mqttBroker[64] = "192.168.150.1";
    int m_displayBrightness = 100;
};

}