#pragma once

#include <cstdint>
#include "core/EventBus.h"

namespace OCC
{

class SystemModel
{
public:

    explicit SystemModel(EventBus *bus);

    void setHeap(uint32_t heap);

    uint32_t heap() const;

private:

    EventBus *m_bus;

    uint32_t m_heap = 0;
};

}