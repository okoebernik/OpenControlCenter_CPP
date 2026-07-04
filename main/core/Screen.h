#pragma once

#include "lvgl.h"

namespace OCC
{

class Screen
{
public:
    virtual ~Screen() = default;

    virtual void create(lv_obj_t *parent) = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void update() {}
};

}