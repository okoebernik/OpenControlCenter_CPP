#include "SplashScreen.h"
#include "Theme.h"
#include "StatusBar.h"
#include "lvgl.h"

namespace OCC
{

void SplashScreen::show()
{
    lv_obj_t *screen = lv_scr_act();

    lv_obj_clean(screen);

    Theme::applyScreen(screen);
	StatusBar statusBar;
	statusBar.create(screen);

    lv_obj_t *title = lv_label_create(screen);

    lv_label_set_text(title, "OpenControlCenter");

    lv_obj_set_style_text_color(
        title,
        Theme::TextPrimary(),
        LV_PART_MAIN);

    lv_obj_align(
        title,
        LV_ALIGN_CENTER,
        0,
        -20);

    lv_obj_t *status = lv_label_create(screen);

    lv_label_set_text(status, "Foundation 0.1");

    lv_obj_set_style_text_color(
        status,
        Theme::Accent(),
        LV_PART_MAIN);

    lv_obj_align(
        status,
        LV_ALIGN_CENTER,
        0,
        20);
}

}