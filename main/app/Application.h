#pragma once

#include "ScreenManager.h"
#include "EventBus.h"
#include "DashboardScreen.h"
#include "SettingsScreen.h"
#include "SystemModel.h"
#include "SystemService.h"
#include "ServiceManager.h"
#include "DashboardViewModel.h"
#include "models/ClockModel.h"
#include "services/ClockService.h"

namespace OCC
{

class Application
{
public:
    void run();

private:
    void initialize();
    void registerScreens();
    void registerEvents();

    static void handleEvent(const Event &event, void *userData);

    ScreenManager m_screenManager;
    EventBus m_eventBus;
	
	bool m_hasPendingScreen = false;
	ScreenId m_pendingScreen = ScreenId::Dashboard;

	void processPendingNavigation();

	DashboardScreen m_dashboardScreen{&m_eventBus};
	SettingsScreen m_settingsScreen{&m_eventBus};
	ServiceManager m_serviceManager;
	SystemModel m_systemModel{&m_eventBus};
	SystemService m_systemService{&m_systemModel};
	DashboardViewModel m_dashboardViewModel{&m_systemModel, &m_clockModel};
	ClockModel m_clockModel;
	ClockService m_clockService{&m_clockModel};
};

}