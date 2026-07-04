#pragma once

#include "lvgl.h"
#include "PrimaryValue.h"
#include "MetricRow.h"

namespace OCC
{

enum class CardStatus
{
    Ok,
    Warning,
    Error,
    Offline
};

class Card
{
public:
    Card() = default;

    void create(lv_obj_t *parent, const char *title);

    void setPosition(int x, int y);
    void setSize(int width, int height);
    void setStatus(CardStatus status);
    void setAccentColor(lv_color_t color);
    void setPrimaryValue(const char *value, const char *unit = "");

    void addValue(const char *label, const char *value);
    MetricRow *addMetric(const char *label, const char *value);

    lv_obj_t *root();

private:
    lv_obj_t *m_root = nullptr;
    lv_obj_t *m_content = nullptr;
    lv_obj_t *m_statusDot = nullptr;
    lv_obj_t *m_accentBar = nullptr;
    PrimaryValue *m_primaryValue = nullptr;
    int m_nextY = 42;
};

}