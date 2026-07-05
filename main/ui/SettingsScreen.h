#pragma once

#include "core/Screen.h"
#include "core/EventBus.h"
#include "NavigationBar.h"
#include "StatusBar.h"
#include "viewmodels/StatusBarViewModel.h"

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

private:
    EventBus *m_eventBus = nullptr;
    lv_obj_t *m_root = nullptr;
	StatusBarViewModel *m_statusBarViewModel = nullptr;
    StatusBar m_statusBar;
    NavigationBar m_navigationBar;
};

}