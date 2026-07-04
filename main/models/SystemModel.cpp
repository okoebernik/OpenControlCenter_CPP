#include "SystemModel.h"
#include <cstdint>

namespace OCC
{

SystemModel::SystemModel(EventBus *bus)
    : m_bus(bus)
{
}

void SystemModel::setHeap(uint32_t heap)
{
    m_heap = heap;

    if (m_bus)
    {
        m_bus->publish({
            EventType::SystemHeapChanged,
            ScreenId::Dashboard,
            heap
        });
    }
}

uint32_t SystemModel::heap() const
{
    return m_heap;
}
}