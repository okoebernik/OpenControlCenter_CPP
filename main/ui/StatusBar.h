#pragma once
#include "viewmodels/StatusBarViewModel.h"
#include "lvgl.h"

namespace OCC
{

class StatusBar
{
public:
    void create(lv_obj_t *parent);
    void update(const char *timeText, const char *wifiText, const char *mqttText);
	void update(const StatusBarViewModel &viewModel);

private:
    lv_obj_t *m_timeLabel = nullptr;
    lv_obj_t *m_wifiLabel = nullptr;
    lv_obj_t *m_mqttLabel = nullptr;
};

}