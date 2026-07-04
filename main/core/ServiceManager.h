#pragma once

#include <cstdint>
#include "Service.h"

namespace OCC
{

class ServiceManager
{
public:
    static constexpr int MaxServices = 16;

    void add(Service *service);
    void begin();
    void update();

private:
    Service *m_services[MaxServices] = {};
    int m_count = 0;
    uint32_t m_lastTickMs = 0;
};

}