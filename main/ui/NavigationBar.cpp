#include "NavigationBar.h"
#include "Theme.h"

namespace OCC
{

NavigationBar::NavigationBar(EventBus *eventBus)
    : m_eventBus(eventBus)
{
}

static lv_obj_t *create_nav_button(lv_obj_t *parent, const char *text, int x)
{
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, 150, 40);
    lv_obj_align(btn, LV_ALIGN_LEFT_MID, x, 0);

    lv_obj_set_style_bg_color(btn, Theme::SurfaceAlt(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(btn, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(btn, 12, LV_PART_MAIN);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, Theme::TextSecondary(), LV_PART_MAIN);
    lv_obj_center(label);

    return btn;
}

void NavigationBar::create(lv_obj_t *parent)
{
    lv_obj_t *bar = lv_obj_create(parent);
    lv_obj_set_size(bar, LV_PCT(100), Theme::NavigationBarHeight);
    lv_obj_align(bar, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_set_style_bg_color(bar, Theme::Surface(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(bar, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(bar, 0, LV_PART_MAIN);
    lv_obj_clear_flag(bar, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *home = create_nav_button(bar, "Home", 30);
    lv_obj_t *dashboard = create_nav_button(bar, "Dashboard", 210);
    lv_obj_t *settings = create_nav_button(bar, "Settings", 570);

    lv_obj_add_event_cb(home, onDashboardClicked, LV_EVENT_CLICKED, this);
    lv_obj_add_event_cb(dashboard, onDashboardClicked, LV_EVENT_CLICKED, this);
    lv_obj_add_event_cb(settings, onSettingsClicked, LV_EVENT_CLICKED, this);

    lv_obj_set_style_bg_color(dashboard, Theme::Accent(), LV_PART_MAIN);
}

void NavigationBar::onDashboardClicked(lv_event_t *event)
{
    auto *nav = static_cast<NavigationBar *>(lv_event_get_user_data(event));

    if (nav && nav->m_eventBus)
    {
        nav->m_eventBus->publish({ EventType::NavigateToScreen, ScreenId::Dashboard, 0 });
    }
}

void NavigationBar::onSettingsClicked(lv_event_t *event)
{
    auto *nav = static_cast<NavigationBar *>(lv_event_get_user_data(event));

    if (nav && nav->m_eventBus)
    {
        nav->m_eventBus->publish({ EventType::NavigateToScreen, ScreenId::Settings, 0 });
    }
}

}