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

    void create(lv_obj_t *parent) override;
    void show() override;
    void hide() override;
    void update() override;

private:
    EventBus *m_eventBus = nullptr;
    lv_obj_t *m_root = nullptr;
    NavigationBar m_navigationBar;
};

}