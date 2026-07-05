#include "StatusBar.h"
#include "Theme.h"
#include <cstring>

namespace OCC
{

void StatusBar::create(lv_obj_t *parent)
{
    lv_obj_t *bar = lv_obj_create(parent);
    lv_obj_set_size(bar, LV_PCT(100), Theme::StatusBarHeight);
    lv_obj_align(bar, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_set_style_bg_color(bar, Theme::Surface(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(bar, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(bar, 0, LV_PART_MAIN);
    lv_obj_clear_flag(bar, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *title = lv_label_create(bar);
    lv_label_set_text(title, "OpenControlCenter");
    lv_obj_set_style_text_color(title, Theme::TextPrimary(), LV_PART_MAIN);
    lv_obj_align(title, LV_ALIGN_LEFT_MID, 12, 0);

    m_mqttLabel = lv_label_create(bar);
    lv_label_set_text(m_mqttLabel, "MQTT -");
    lv_obj_set_style_text_color(m_mqttLabel, Theme::TextSecondary(), LV_PART_MAIN);
    lv_obj_align(m_mqttLabel, LV_ALIGN_RIGHT_MID, -12, 0);

    m_wifiLabel = lv_label_create(bar);
    lv_label_set_text(m_wifiLabel, "WiFi -");
    lv_obj_set_style_text_color(m_wifiLabel, Theme::TextSecondary(), LV_PART_MAIN);
    lv_obj_align_to(m_wifiLabel, m_mqttLabel, LV_ALIGN_OUT_LEFT_MID, -24, 0);

    m_timeLabel = lv_label_create(bar);
    lv_label_set_text(m_timeLabel, "00:00");
    lv_obj_set_style_text_color(m_timeLabel, Theme::Accent(), LV_PART_MAIN);
    lv_obj_align_to(m_timeLabel, m_wifiLabel, LV_ALIGN_OUT_LEFT_MID, -24, 0);
}

void StatusBar::update(const char *timeText, const char *wifiText, const char *mqttText)
{
    if (m_timeLabel && std::strcmp(lv_label_get_text(m_timeLabel), timeText) != 0)
    {
        lv_label_set_text(m_timeLabel, timeText);
    }

    if (m_wifiLabel && std::strcmp(lv_label_get_text(m_wifiLabel), wifiText) != 0)
    {
        lv_label_set_text(m_wifiLabel, wifiText);
    }

    if (m_mqttLabel && std::strcmp(lv_label_get_text(m_mqttLabel), mqttText) != 0)
    {
        lv_label_set_text(m_mqttLabel, mqttText);
    }
}
void StatusBar::update(const StatusBarViewModel &viewModel)
{
	update(
		viewModel.clockText(),
		viewModel.wifiText(),
		viewModel.mqttText()
	);
}
}