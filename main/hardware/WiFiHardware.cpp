#include "WiFiHardware.h"

#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_netif_ip_addr.h"
#include <cstdio>
#include <cstring>

namespace OCC
{

static const char *TAG = "WiFiHardware";

static bool s_initialized = false;
static esp_netif_t *s_staNetif = nullptr;

void WiFiHardware::begin()
{
    if (s_initialized)
    {
        return;
    }

    ESP_LOGI(TAG, "Initializing WiFi hardware");

    ESP_ERROR_CHECK(esp_netif_init());

    esp_err_t eventLoopResult = esp_event_loop_create_default();
    if (eventLoopResult != ESP_OK && eventLoopResult != ESP_ERR_INVALID_STATE)
    {
        ESP_ERROR_CHECK(eventLoopResult);
    }

    s_staNetif = esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    s_initialized = true;
}

void WiFiHardware::connect(const char *ssid, const char *password)
{
    if (!s_initialized)
    {
        begin();
    }

    wifi_config_t wifi_config = {};

    std::strncpy(
        reinterpret_cast<char *>(wifi_config.sta.ssid),
        ssid,
        sizeof(wifi_config.sta.ssid)
    );

    std::strncpy(
        reinterpret_cast<char *>(wifi_config.sta.password),
        password,
        sizeof(wifi_config.sta.password)
    );

    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));

    ESP_LOGI(TAG, "Connecting to SSID: %s", ssid);
    esp_wifi_connect();
}

bool WiFiHardware::isConnected()
{
    wifi_ap_record_t ap_info;
    return esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK;
}
void WiFiHardware::getIpText(char *buffer, int bufferSize)
{
    if (!buffer || bufferSize <= 0)
    {
        return;
    }

    snprintf(buffer, bufferSize, "0.0.0.0");

    if (!s_staNetif)
    {
        return;
    }

    esp_netif_ip_info_t ipInfo;
    if (esp_netif_get_ip_info(s_staNetif, &ipInfo) != ESP_OK)
    {
        return;
    }

    snprintf(
        buffer,
        bufferSize,
        IPSTR,
        IP2STR(&ipInfo.ip)
    );
}
}