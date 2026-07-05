#include "ClockService.h"

#include "esp_log.h"
#include "esp_sntp.h"
#include <ctime>
#include <cstdio>

namespace OCC
{

static const char *TAG = "ClockService";

ClockService::ClockService(ClockModel *model)
    : m_model(model)
{
}

void ClockService::begin()
{
    ESP_LOGI(TAG, "ClockService started");
}
void ClockService::startSntp()
{
    if (m_sntpStarted)
    {
        return;
    }

    ESP_LOGI(TAG, "Starting SNTP");

    esp_sntp_setoperatingmode(SNTP_OPMODE_POLL);
    esp_sntp_setservername(0, "pool.ntp.org");
    esp_sntp_init();

    // Deutschland: UTC+1, Sommerzeit automatisch nach EU-Regel
    setenv("TZ", "CET-1CEST,M3.5.0/2,M10.5.0/3", 1);
    tzset();

    m_sntpStarted = true;
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
    m_seconds++;

    if (!m_model)
    {
        return;
    }
	
	if (!m_sntpStarted)
	{
		startSntp();
	}
    char buffer[16];

    time_t now;
    time(&now);

    // Wenn die Zeit noch nicht gesetzt ist, ist sie meist nahe 1970.
    if (isTimeValid())
    {
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
        uint32_t minutes = (m_seconds / 60) % 60;
        uint32_t hours = (m_seconds / 3600) % 24;

        snprintf(
            buffer,
            sizeof(buffer),
            "%02lu:%02lu",
            static_cast<unsigned long>(hours),
            static_cast<unsigned long>(minutes)
        );
    }

    m_model->setTimeText(buffer);
}

}