#include "WiFiService.h"
#include "WiFiSecrets.h"
#include "hardware/WiFiHardware.h"

#include "esp_log.h"

namespace OCC
{

static const char *TAG = "WiFiService";

WiFiService::WiFiService(WiFiModel *model)
    : m_model(model)
{
}

void WiFiService::begin()
{
    ESP_LOGI(TAG, "WiFiService started");

    if (m_model)
    {
        m_model->setConnected(false);
        m_model->setIpText("0.0.0.0");
    }

    WiFiHardware::begin();
    WiFiHardware::connect(OCC_WIFI_SSID, OCC_WIFI_PASSWORD);
}

void WiFiService::update(uint32_t deltaMs)
{
    (void)deltaMs;

    bool connected = WiFiHardware::isConnected();

    if (m_model)
    {
        m_model->setConnected(connected);
        m_model->setIpText(connected ? "connected" : "0.0.0.0");
    }
}

}