#pragma once

#include "ViewModel.h"
#include "models/ClockModel.h"
#include "models/WiFiModel.h"

namespace OCC
{

class StatusBarViewModel : public ViewModel
{
public:
    StatusBarViewModel(ClockModel *clockModel, WiFiModel *wifiModel);

    void update() override;

    const char *clockText() const;
    const char *wifiText() const;
    const char *mqttText() const;

private:
    ClockModel *m_clockModel = nullptr;
    WiFiModel *m_wifiModel = nullptr;

    char m_clockText[16] = "00:00";
    char m_wifiText[16] = "WiFi -";
    char m_mqttText[16] = "MQTT -";
};

}