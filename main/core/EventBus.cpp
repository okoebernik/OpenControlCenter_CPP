#include "EventBus.h"

namespace OCC
{

void EventBus::subscribe(EventHandler handler, void *userData)
{
    if (m_count >= MaxHandlers)
    {
        return;
    }

    m_handlers[m_count] = handler;
    m_userData[m_count] = userData;
    m_count++;
}

void EventBus::publish(const Event &event)
{
    for (int i = 0; i < m_count; ++i)
    {
        if (m_handlers[i])
        {
            m_handlers[i](event, m_userData[i]);
        }
    }
}

}