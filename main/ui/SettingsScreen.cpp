#include "SettingsScreen.h"
#include "Theme.h"
#include "StatusBar.h"
#include "NavigationBar.h"

#include "lvgl.h"

namespace OCC
{
SettingsScreen::SettingsScreen(EventBus *eventBus)
    : m_eventBus(eventBus),
	  m_navigationBar(eventBus)
{
}
void SettingsScreen::create(lv_obj_t *parent)
{
    m_root = lv_obj_create(parent);
    lv_obj_set_size(m_root, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_border_width(m_root, 0, LV_PART_MAIN);
    lv_obj_clear_flag(m_root, LV_OBJ_FLAG_SCROLLABLE);

    Theme::applyScreen(m_root);

    StatusBar statusBar;
    statusBar.create(m_root);
    statusBar.update("10:42", "WiFi -", "MQTT -");

    m_navigationBar.create(m_root);

    lv_obj_t *title = lv_label_create(m_root);
    lv_label_set_text(title, "Settings");
    lv_obj_set_style_text_color(title, Theme::TextPrimary(), LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_CENTER, 0, -40);

    lv_obj_t *sub = lv_label_create(m_root);
    lv_label_set_text(sub, "System configuration will be here");
    lv_obj_set_style_text_color(sub, Theme::TextSecondary(), LV_PART_MAIN);
    lv_obj_align(sub, LV_ALIGN_CENTER, 0, 0);
}

void SettingsScreen::show()
{
    if (m_root)
    {
        lv_obj_clear_flag(m_root, LV_OBJ_FLAG_HIDDEN);
    }
}

void SettingsScreen::hide()
{
    if (m_root)
    {
        lv_obj_add_flag(m_root, LV_OBJ_FLAG_HIDDEN);
    }
}

void SettingsScreen::update()
{
}

}