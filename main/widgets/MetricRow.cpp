#include "MetricRow.h"
#include "Theme.h"

#include <cstring>

namespace OCC
{

MetricRow::MetricRow(lv_obj_t *parent, const char *label, const char *value)
{
    m_root = lv_obj_create(parent);
    lv_obj_set_height(m_root, 24);
    lv_obj_set_width(m_root, 210);

    lv_obj_set_style_bg_opa(m_root, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(m_root, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(m_root, 0, LV_PART_MAIN);
    lv_obj_clear_flag(m_root, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_flex_flow(m_root, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(
        m_root,
        LV_FLEX_ALIGN_SPACE_BETWEEN,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER
    );

    m_label = lv_label_create(m_root);
    lv_label_set_text(m_label, label);
    lv_obj_set_style_text_color(m_label, Theme::TextSecondary(), LV_PART_MAIN);

    m_value = lv_label_create(m_root);
    lv_label_set_text(m_value, value);
    lv_obj_set_style_text_color(m_value, Theme::TextPrimary(), LV_PART_MAIN);
}

void MetricRow::setPosition(int x, int y)
{
    if (m_root)
    {
        lv_obj_set_pos(m_root, x, y);
    }
}

void MetricRow::setWidth(int width)
{
    if (m_root)
    {
        lv_obj_set_width(m_root, width);
    }
}

void MetricRow::setValue(const char *value)
{
    if (!m_value || !value)
    {
        return;
    }

    if (std::strcmp(lv_label_get_text(m_value), value) != 0)
    {
        lv_label_set_text(m_value, value);
    }
}

}