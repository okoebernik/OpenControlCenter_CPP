#include "PrimaryValue.h"
#include "Theme.h"
#include <cstring>

namespace OCC
{

PrimaryValue::PrimaryValue(lv_obj_t *parent, const char *value, const char *unit)
{
    m_valueLabel = lv_label_create(parent);
    lv_label_set_text(m_valueLabel, value);
    lv_obj_set_style_text_color(m_valueLabel, Theme::TextPrimary(), LV_PART_MAIN);

    m_unitLabel = lv_label_create(parent);
    lv_label_set_text(m_unitLabel, unit);
    lv_obj_set_style_text_color(m_unitLabel, Theme::TextSecondary(), LV_PART_MAIN);
	
	lv_obj_set_style_text_font(m_valueLabel, &lv_font_montserrat_32, LV_PART_MAIN);
	lv_obj_set_style_text_font(m_unitLabel, &lv_font_montserrat_20, LV_PART_MAIN);
}

void PrimaryValue::setPosition(int x, int y)
{
    lv_obj_set_pos(m_valueLabel, x, y);
    lv_obj_align_to(m_unitLabel, m_valueLabel, LV_ALIGN_OUT_RIGHT_BOTTOM, 6, -2);
}

void PrimaryValue::setValue(const char *value)
{
    if (!m_valueLabel || !value)
    {
        return;
    }

    if (std::strcmp(lv_label_get_text(m_valueLabel), value) != 0)
    {
        lv_label_set_text(m_valueLabel, value);
    }
}

}