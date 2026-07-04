#pragma once

#include "lvgl.h"
#include "core/EventBus.h"

namespace OCC
{

class NavigationBar
{
public:
    explicit NavigationBar(EventBus *eventBus);

    void create(lv_obj_t *parent);

private:
    static void onDashboardClicked(lv_event_t *event);
    static void onSettingsClicked(lv_event_t *event);

    EventBus *m_eventBus;
};

}