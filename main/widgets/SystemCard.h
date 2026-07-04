#pragma once

#include <cstdint>

#include "lvgl.h"
#include "Card.h"
#include "MetricRow.h"
#include "viewmodels/DashboardViewModel.h"

namespace OCC
{

class SystemCard
{
public:
    SystemCard() = default;

    void create(lv_obj_t *parent);

    void setPosition(int x, int y);
    void setSize(int width, int height);
    void setHeap(uint32_t heapBytes);
	void update(const DashboardViewModel &viewModel);

    Card &card();

private:
    Card m_card;
    MetricRow *m_heapRow = nullptr;
};

}