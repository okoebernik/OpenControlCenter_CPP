#include "SystemService.h"

#include "esp_heap_caps.h"
#include "esp_log.h"

namespace OCC
{

static const char *TAG = "SystemService";

SystemService::SystemService(SystemModel *model)
    : m_model(model)
{
}

void SystemService::begin()
{
    ESP_LOGI(TAG, "SystemService started");
}

void SystemService::update(uint32_t deltaMs)
{
    m_elapsedMs += deltaMs;

    if (m_elapsedMs < 1000)
    {
        return;
    }

    m_elapsedMs = 0;

    if (!m_model)
    {
        return;
    }

    uint32_t freeHeap = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
    m_model->setHeap(freeHeap);

    ESP_LOGI(TAG, "Free heap: %lu bytes", static_cast<unsigned long>(freeHeap));
}

}