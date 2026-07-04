#pragma once

#include "lvgl.h"

namespace OCC
{

class Theme
{
public:
    static constexpr int SpaceXS = 4;
    static constexpr int SpaceS  = 8;
    static constexpr int SpaceM  = 16;
    static constexpr int SpaceL  = 24;
    static constexpr int SpaceXL = 32;

    static constexpr int StatusBarHeight = 40;
    static constexpr int NavigationBarHeight = 56;

    static lv_color_t Background();
    static lv_color_t Surface();
    static lv_color_t SurfaceAlt();
    static lv_color_t Accent();
    static lv_color_t Success();
    static lv_color_t Warning();
    static lv_color_t Error();
    static lv_color_t TextPrimary();
    static lv_color_t TextSecondary();

    static void applyScreen(lv_obj_t *screen);
    static void applyCard(lv_obj_t *card);
};

}