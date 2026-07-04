#pragma once

#include "core/Screen.h"
#include "core/EventBus.h"
#include "NavigationBar.h"
#include "widgets/SystemCard.h"
#include "widgets/Card.h"
#include "viewmodels/DashboardViewModel.h"
#include "StatusBar.h"

namespace OCC
{

class DashboardScreen : public Screen
{
public:
    explicit DashboardScreen(EventBus *eventBus);

    void setViewModel(DashboardViewModel *viewModel);

    void create(lv_obj_t *parent) override;
    void show() override;
    void hide() override;
    void update() override;

private:
    EventBus *m_eventBus = nullptr;
    DashboardViewModel *m_viewModel = nullptr;

    lv_obj_t *m_root = nullptr;

    NavigationBar m_navigationBar;
	StatusBar m_statusBar;
    Card m_aquariumCard;
    Card m_victronCard;
    Card m_weatherCard;
    Card m_synologyCard;
    Card m_proxmoxCard;

    SystemCard m_systemCard;
};

}