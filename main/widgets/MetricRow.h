#pragma once

#include "lvgl.h"

namespace OCC
{

class MetricRow
{
public:
    MetricRow(lv_obj_t *parent, const char *label, const char *value);

    void setPosition(int x, int y);
    void setWidth(int width);
    void setValue(const char *value);

private:
    lv_obj_t *m_label = nullptr;
    lv_obj_t *m_value = nullptr;
    int m_width = 200;
};

}