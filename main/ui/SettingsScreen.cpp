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
void SettingsScreen::show()
{
    lv_obj_t *screen = lv_scr_act();
    lv_obj_clean(screen);

    Theme::applyScreen(screen);

    StatusBar statusBar;
    statusBar.create(screen);
    statusBar.update("10:42", "WiFi -", "MQTT -");

    m_navigationBar.create(screen);

    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "Settings");
    lv_obj_set_style_text_color(title, Theme::TextPrimary(), LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_CENTER, 0, -40);

    lv_obj_t *sub = lv_label_create(screen);
    lv_label_set_text(sub, "System configuration will be here");
    lv_obj_set_style_text_color(sub, Theme::TextSecondary(), LV_PART_MAIN);
    lv_obj_align(sub, LV_ALIGN_CENTER, 0, 0);
}

void SettingsScreen::update()
{
}

}