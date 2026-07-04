#pragma once

#include "Screen.h"

namespace OCC
{

enum class ScreenId
{
    Dashboard,
    Settings
};

class ScreenManager
{
public:
    void registerScreen(ScreenId id, Screen *screen);
    void show(ScreenId id);
    void update();

private:
    Screen *m_dashboardScreen = nullptr;
    Screen *m_settingsScreen = nullptr;
    Screen *m_currentScreen = nullptr;
	ScreenId m_currentId = ScreenId::Dashboard;
	bool m_hasCurrentId = false;
};

}