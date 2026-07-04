#include "SystemCard.h"

#include <cstdio>

namespace OCC
{

void SystemCard::create(lv_obj_t *parent)
{
    m_card.create(parent, "System");
    m_card.setAccentColor(lv_color_hex(0x90A4AE));
    m_card.setStatus(CardStatus::Ok);
    m_card.setPrimaryValue("OK", "");
    m_heapRow = m_card.addMetric("Heap", "--- KB");
    m_card.addValue("Flash", "32 MB");
}

void SystemCard::setPosition(int x, int y)
{
    m_card.setPosition(x, y);
}

void SystemCard::setSize(int width, int height)
{
    m_card.setSize(width, height);
}

void SystemCard::setHeap(uint32_t heapBytes)
{
    if (!m_heapRow)
    {
        return;
    }

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%lu KB", static_cast<unsigned long>(heapBytes / 1024));
    m_heapRow->setValue(buffer);
}

Card &SystemCard::card()
{
    return m_card;
}

}