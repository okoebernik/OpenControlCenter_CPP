#include "ClockService.h"

#include "esp_log.h"

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

void ClockService::update(uint32_t deltaMs)
{
    m_elapsedMs += deltaMs;

    if (m_elapsedMs < 1000)
    {
        return;
    }

    m_elapsedMs = 0;
    m_seconds++;

    if (m_model)
    {
        m_model->setSeconds(m_seconds);
    }
}

}