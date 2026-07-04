#pragma once

#include "Card.h"

namespace OCC
{

class LayoutManager
{
public:
    LayoutManager(int startX, int startY, int columns, int cardWidth, int cardHeight, int spacing);

    void add(Card &card);

private:
    int m_startX;
    int m_startY;
    int m_columns;
    int m_cardWidth;
    int m_cardHeight;
    int m_spacing;
    int m_index = 0;
};

}