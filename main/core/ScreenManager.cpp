#include "ScreenManager.h"

namespace OCC
{

void ScreenManager::registerScreen(ScreenId id, Screen *screen)
{
    switch (id)
    {
        case ScreenId::Dashboard:
            m_dashboardScreen = screen;
            break;

        case ScreenId::Settings:
            m_settingsScreen = screen;
            break;
    }
}

void ScreenManager::show(ScreenId id)
{
    if (m_hasCurrentId && m_currentId == id)
    {
        return;
    }

    if (m_currentScreen)
    {
        m_currentScreen->hide();
    }

    m_currentId = id;
    m_hasCurrentId = true;

    switch (id)
    {
        case ScreenId::Dashboard:
            m_currentScreen = m_dashboardScreen;
            break;

        case ScreenId::Settings:
            m_currentScreen = m_settingsScreen;
            break;
    }

    if (m_currentScreen)
    {
        m_currentScreen->show();
    }
}

void ScreenManager::update()
{
    if (m_currentScreen)
    {
        m_currentScreen->update();
    }
}
void ScreenManager::create(lv_obj_t *parent)
{
    if (m_dashboardScreen)
    {
        m_dashboardScreen->create(parent);
        m_dashboardScreen->hide();
    }

    if (m_settingsScreen)
    {
        m_settingsScreen->create(parent);
        m_settingsScreen->hide();
    }
}
}