#pragma once

#include "core/Screen.h"
#include "core/EventBus.h"
#include "NavigationBar.h"
#include "StatusBar.h"
#include "viewmodels/StatusBarViewModel.h"
#include "viewmodels/SettingsViewModel.h"
#include "widgets/Card.h"
#include "widgets/MetricRow.h"
#include "widgets/IconButton.h"

namespace OCC
{

class SettingsScreen : public Screen
{
public:
    explicit SettingsScreen(EventBus *eventBus);
	
	void setStatusBarViewModel(StatusBarViewModel *viewModel);
    void create(lv_obj_t *parent) override;
    void show() override;
    void hide() override;
    void update() override;
	void setViewModel(SettingsViewModel *viewModel);

private:
    EventBus *m_eventBus = nullptr;
    lv_obj_t *m_root = nullptr;
	StatusBarViewModel *m_statusBarViewModel = nullptr;
    StatusBar m_statusBar;
    NavigationBar m_navigationBar;
	SettingsViewModel *m_viewModel = nullptr;

	Card m_systemSettingsCard;
	Card m_networkSettingsCard;
	MetricRow *m_hostnameRow = nullptr;
	MetricRow *m_brightnessRow = nullptr;
	MetricRow *m_wifiSsidRow = nullptr;
	MetricRow *m_mqttBrokerRow = nullptr;
	
	IconButton m_brightnessMinusButton;
	IconButton m_brightnessPlusButton;
	
	static void onBrightnessMinus(void *userData);
	static void onBrightnessPlus(void *userData);
};

}