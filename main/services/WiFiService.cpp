#include "WiFiService.h"
#include "core/Configuration.h"
#include "hardware/WiFiHardware.h"
#include "WiFiSecrets.h"
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

    auto &config = Configuration::instance();

    if (!config.isInitialized())
    {
        ESP_LOGI(TAG, "Running first start configuration");

        config.setWifiSsid(OCC_WIFI_SSID);
        config.setWifiPassword(OCC_WIFI_PASSWORD);

        config.setInitialized(true);
        config.save();
    }

    WiFiHardware::begin();

    if (config.wifiSsid()[0] != '\0')
    {
        WiFiHardware::connect(config.wifiSsid(), config.wifiPassword());
    }
    else
    {
        ESP_LOGW(TAG, "No WiFi SSID configured");
    }
}
void WiFiService::update(uint32_t deltaMs)
{
    (void)deltaMs;

    bool connected = WiFiHardware::isConnected();

	if (m_model)
	{
		m_model->setConnected(connected);

		char ipText[32];
		WiFiHardware::getIpText(ipText, sizeof(ipText));
		m_model->setIpText(ipText);
	}
}

}