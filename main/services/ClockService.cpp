#include "ClockService.h"

#include "esp_log.h"
#include "esp_sntp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <ctime>
#include <cstdio>
#include <cstdlib>

namespace OCC
{

static const char *TAG = "ClockService";

ClockService::ClockService(ClockModel *clockModel, WiFiModel *wifiModel)
    : m_clockModel(clockModel),
      m_wifiModel(wifiModel)
{
}

void ClockService::begin()
{
    ESP_LOGI(TAG, "ClockService started");

    setenv("TZ", "CET-1CEST,M3.5.0/2,M10.5.0/3", 1);
    tzset();
}

void ClockService::startSntp()
{
    if (m_sntpStarted || m_sntpStartRequested)
    {
        return;
    }

    m_sntpStartRequested = true;

    xTaskCreate(
        sntpStartTask,
        "sntp_start",
        8192,
        this,
        3,
        nullptr
    );
}

bool ClockService::isTimeValid() const
{
    time_t now;
    time(&now);

    return now > 1700000000;
}

void ClockService::update(uint32_t deltaMs)
{
    m_elapsedMs += deltaMs;

    if (m_elapsedMs < 1000)
    {
        return;
    }

    m_elapsedMs = 0;
    m_uptimeSeconds++;

    if (!m_clockModel)
    {
        return;
    }

    if (m_wifiModel && m_wifiModel->hasIp() && !m_sntpStarted)
	{
		startSntp();
	}

    char buffer[16];

    if (isTimeValid())
    {
        time_t now;
        time(&now);

        struct tm timeinfo;
        localtime_r(&now, &timeinfo);

        snprintf(
            buffer,
            sizeof(buffer),
            "%02d:%02d",
            timeinfo.tm_hour,
            timeinfo.tm_min
        );
    }
    else
    {
        uint32_t minutes = (m_uptimeSeconds / 60) % 60;
        uint32_t hours = (m_uptimeSeconds / 3600) % 24;

        snprintf(
            buffer,
            sizeof(buffer),
            "%02lu:%02lu",
            static_cast<unsigned long>(hours),
            static_cast<unsigned long>(minutes)
        );
    }

    m_clockModel->setTimeText(buffer);
}
void ClockService::sntpStartTask(void *param)
{
    auto *self = static_cast<ClockService *>(param);

    if (!self)
    {
        vTaskDelete(nullptr);
        return;
    }

    ESP_LOGI(TAG, "Starting SNTP");

    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");
    esp_sntp_setservername(1, "time.google.com");
    esp_sntp_init();

    self->m_sntpStarted = true;

    vTaskDelete(nullptr);
}
}