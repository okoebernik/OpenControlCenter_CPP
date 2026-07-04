#include "LayoutManager.h"

namespace OCC
{

LayoutManager::LayoutManager(
    int startX,
    int startY,
    int columns,
    int cardWidth,
    int cardHeight,
    int spacing)
    : m_startX(startX),
      m_startY(startY),
      m_columns(columns),
      m_cardWidth(cardWidth),
      m_cardHeight(cardHeight),
      m_spacing(spacing)
{
}

void LayoutManager::add(Card &card)
{
    int column = m_index % m_columns;
    int row = m_index / m_columns;

    int x = m_startX + column * (m_cardWidth + m_spacing);
    int y = m_startY + row * (m_cardHeight + m_spacing);

    card.setPosition(x, y);
    card.setSize(m_cardWidth, m_cardHeight);

    m_index++;
}

}