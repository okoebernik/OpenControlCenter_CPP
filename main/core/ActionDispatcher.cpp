#include "ActionDispatcher.h"

namespace OCC
{

void ActionDispatcher::setHandler(Handler handler, void *userData)
{
    m_handler = handler;
    m_userData = userData;
}

void ActionDispatcher::dispatch(UIAction action)
{
    if (m_handler)
    {
        m_handler(action, m_userData);
    }
}

}