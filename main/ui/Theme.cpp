#include "Theme.h"

namespace OCC
{

lv_color_t Theme::Background()    { return lv_color_hex(0x16181D); }
lv_color_t Theme::Surface()       { return lv_color_hex(0x23262E); }
lv_color_t Theme::SurfaceAlt()    { return lv_color_hex(0x2D313A); }
lv_color_t Theme::Accent()        { return lv_color_hex(0x2EA8FF); }
lv_color_t Theme::Success()       { return lv_color_hex(0x4CAF50); }
lv_color_t Theme::Warning()       { return lv_color_hex(0xFFB300); }
lv_color_t Theme::Error()         { return lv_color_hex(0xF44336); }
lv_color_t Theme::TextPrimary()   { return lv_color_hex(0xFFFFFF); }
lv_color_t Theme::TextSecondary() { return lv_color_hex(0xB6BEC9); }

void Theme::applyScreen(lv_obj_t *screen)
{
    lv_obj_set_style_bg_color(screen, Background(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, LV_PART_MAIN);
}

void Theme::applyCard(lv_obj_t *card)
{
    lv_obj_set_style_bg_color(card, Surface(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(card, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(card, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(card, SurfaceAlt(), LV_PART_MAIN);
    lv_obj_set_style_radius(card, 18, LV_PART_MAIN);
    lv_obj_set_style_pad_all(card, SpaceM, LV_PART_MAIN);
    lv_obj_clear_flag(card, LV_OBJ_FLAG_SCROLLABLE);
}

}