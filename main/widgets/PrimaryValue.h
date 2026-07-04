#pragma once

#include "lvgl.h"

namespace OCC
{

class PrimaryValue
{
public:
    PrimaryValue(lv_obj_t *parent, const char *value, const char *unit = "");

    void setPosition(int x, int y);
    void setValue(const char *value);

private:
    lv_obj_t *m_valueLabel = nullptr;
    lv_obj_t *m_unitLabel = nullptr;
};

}