#include "ServiceManager.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace OCC
{

void ServiceManager::add(Service *service)
{
    if (!service || m_count >= MaxServices)
    {
        return;
    }

    m_services[m_count++] = service;
}

void ServiceManager::begin()
{
    m_lastTickMs = xTaskGetTickCount() * portTICK_PERIOD_MS;

    for (int i = 0; i < m_count; ++i)
    {
        m_services[i]->begin();
    }
}

void ServiceManager::update()
{
    uint32_t nowMs = xTaskGetTickCount() * portTICK_PERIOD_MS;
    uint32_t deltaMs = nowMs - m_lastTickMs;
    m_lastTickMs = nowMs;

    for (int i = 0; i < m_count; ++i)
    {
        m_services[i]->update(deltaMs);
    }
}

}