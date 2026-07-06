#include "SettingsViewModel.h"
#include "core/Configuration.h"
#include <cstdio>

namespace OCC
{

void SettingsViewModel::update()
{
    auto &config = Configuration::instance();

    snprintf(m_hostnameText, sizeof(m_hostnameText), "%s", config.hostname());
    snprintf(m_wifiSsidText, sizeof(m_wifiSsidText), "%s", config.wifiSsid());

    snprintf(
        m_mqttBrokerText,
        sizeof(m_mqttBrokerText),
        "%s:%d",
        config.mqttBroker(),
        config.mqttPort()
    );

    snprintf(
        m_brightnessText,
        sizeof(m_brightnessText),
        "%d %%",
        config.displayBrightness()
    );
}

const char *SettingsViewModel::hostnameText() const
{
    return m_hostnameText;
}

const char *SettingsViewModel::wifiSsidText() const
{
    return m_wifiSsidText;
}

const char *SettingsViewModel::mqttBrokerText() const
{
    return m_mqttBrokerText;
}

const char *SettingsViewModel::brightnessText() const
{
    return m_brightnessText;
}
void SettingsViewModel::increaseBrightness()
{
    auto &config = Configuration::instance();

    int value = config.displayBrightness();
    value += 10;

    config.setDisplayBrightness(value);
    config.save();

    update();
}

void SettingsViewModel::decreaseBrightness()
{
    auto &config = Configuration::instance();

    int value = config.displayBrightness();
    value -= 10;

    config.setDisplayBrightness(value);
    config.save();

    update();
}
}