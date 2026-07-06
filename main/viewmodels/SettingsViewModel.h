#pragma once

#include "ViewModel.h"
#include <cstdio>


namespace OCC
{

class SettingsViewModel : public ViewModel
{
public:
    SettingsViewModel() = default;

    void update() override;
	void increaseBrightness();
	void decreaseBrightness();

    const char *hostnameText() const;
    const char *wifiSsidText() const;
    const char *mqttBrokerText() const;
    const char *brightnessText() const;

private:
    char m_hostnameText[40] = "";
    char m_wifiSsidText[40] = "";
    char m_mqttBrokerText[80] = "";
    char m_brightnessText[24] = "";
};

} // namespace OCC