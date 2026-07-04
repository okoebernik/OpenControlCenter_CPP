#include "MetricRow.h"
#include "Theme.h"

namespace OCC
{

MetricRow::MetricRow(lv_obj_t *parent, const char *label, const char *value)
{
    m_label = lv_label_create(parent);
    lv_label_set_text(m_label, label);
    lv_obj_set_style_text_color(m_label, Theme::TextSecondary(), LV_PART_MAIN);

    m_value = lv_label_create(parent);
    lv_label_set_text(m_value, value);
    lv_obj_set_style_text_color(m_value, Theme::Accent(), LV_PART_MAIN);
}

void MetricRow::setPosition(int x, int y)
{
    lv_obj_set_pos(m_label, x, y);
    lv_obj_set_pos(m_value, x + m_width - 80, y);
}

void MetricRow::setWidth(int width)
{
    m_width = width;
}

void MetricRow::setValue(const char *value)
{
    if (m_value)
    {
        lv_label_set_text(m_value, value);
    }
}

}