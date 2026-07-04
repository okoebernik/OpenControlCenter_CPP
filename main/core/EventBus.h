#pragma once

#include <cstdint>
#include "ScreenManager.h"

namespace OCC
{

enum class EventType
{
    NavigateToScreen,
    ClockTick,
    WifiStatusChanged,
    MqttStatusChanged,
    SystemHeapChanged
};

struct Event
{
    EventType type;
    ScreenId screenId;
    uint32_t value;
};

using EventHandler = void (*)(const Event &event, void *userData);

class EventBus
{
public:
    static constexpr int MaxHandlers = 16;

    void subscribe(EventHandler handler, void *userData);
    void publish(const Event &event);

private:
    EventHandler m_handlers[MaxHandlers] = {};
    void *m_userData[MaxHandlers] = {};
    int m_count = 0;
};

}