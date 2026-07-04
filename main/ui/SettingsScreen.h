#pragma once

#include "core/Screen.h"
#include "core/EventBus.h"
#include "NavigationBar.h"

namespace OCC
{

class SettingsScreen : public Screen
{
public:
    explicit SettingsScreen(EventBus *eventBus);

    void show() override;
    void update() override;

private:
    EventBus *m_eventBus;
    NavigationBar m_navigationBar;
};

}