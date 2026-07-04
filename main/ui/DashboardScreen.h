#pragma once

#include "core/Screen.h"
#include "core/EventBus.h"
#include "NavigationBar.h"

namespace OCC
{

class DashboardScreen : public Screen
{
public:
    explicit DashboardScreen(EventBus *eventBus);

    void show() override;
    void update() override;

private:
    EventBus *m_eventBus;
    NavigationBar m_navigationBar;
};

}