#include "Card.h"
#include "Theme.h"
#include "MetricRow.h"
#include "PrimaryValue.h"

namespace OCC
{

void Card::create(lv_obj_t *parent, const char *title)
{
    m_root = lv_obj_create(parent);
    lv_obj_set_size(m_root, 240, 160);
    Theme::applyCard(m_root);
	
	m_accentBar = lv_obj_create(m_root);
	lv_obj_set_size(m_accentBar, 5, LV_PCT(100));
	lv_obj_align(m_accentBar, LV_ALIGN_LEFT_MID, 0, 0);
	lv_obj_set_style_bg_color(m_accentBar, Theme::Accent(), LV_PART_MAIN);
	lv_obj_set_style_bg_opa(m_accentBar, LV_OPA_COVER, LV_PART_MAIN);
	lv_obj_set_style_border_width(m_accentBar, 0, LV_PART_MAIN);
	lv_obj_set_style_radius(m_accentBar, 0, LV_PART_MAIN);
	lv_obj_clear_flag(m_accentBar, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *titleLabel = lv_label_create(m_root);
    lv_label_set_text(titleLabel, title);
    lv_obj_set_style_text_color(titleLabel, Theme::TextPrimary(), LV_PART_MAIN);
    lv_obj_set_pos(titleLabel, Theme::SpaceM, Theme::SpaceS);

    m_statusDot = lv_obj_create(m_root);
    lv_obj_set_size(m_statusDot, 12, 12);
    lv_obj_align(m_statusDot, LV_ALIGN_TOP_RIGHT, -16, 14);
    lv_obj_set_style_radius(m_statusDot, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_style_border_width(m_statusDot, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(m_statusDot, Theme::Success(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(m_statusDot, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_clear_flag(m_statusDot, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *line = lv_obj_create(m_root);
    lv_obj_set_size(line, LV_PCT(90), 1);
    lv_obj_set_pos(line, Theme::SpaceM, 36);
    lv_obj_set_style_bg_color(line, Theme::SurfaceAlt(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(line, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_border_width(line, 0, LV_PART_MAIN);
    lv_obj_clear_flag(line, LV_OBJ_FLAG_SCROLLABLE);

    m_content = m_root;
    m_nextY = 52;
}

void Card::setPosition(int x, int y)
{
    lv_obj_set_pos(m_root, x, y);
}

void Card::setSize(int width, int height)
{
    lv_obj_set_size(m_root, width, height);
}
void Card::setPrimaryValue(const char *value, const char *unit)
{
    if (!m_primaryValue)
    {
        m_primaryValue = new PrimaryValue(m_content, value, unit);
        m_primaryValue->setPosition(Theme::SpaceM, 48);
        m_nextY = 92;
        return;
    }

    m_primaryValue->setValue(value);
}
void Card::addValue(const char *label, const char *value)
{
    MetricRow row(m_content, label, value);
    row.setWidth(200);
    row.setPosition(Theme::SpaceM, m_nextY);

    m_nextY += 26;
}

MetricRow *Card::addMetric(const char *label, const char *value)
{
	auto *row = new MetricRow(m_content, label, value);
	row->setWidth(200);
	row->setPosition(Theme::SpaceM, m_nextY);
	m_nextY += 26;
	return row;
}

void Card::setStatus(CardStatus status)
{
    if (!m_statusDot)
    {
        return;
    }

    lv_color_t color = Theme::TextSecondary();

    switch (status)
    {
        case CardStatus::Ok:
            color = Theme::Success();
            break;

        case CardStatus::Warning:
            color = Theme::Warning();
            break;

        case CardStatus::Error:
            color = Theme::Error();
            break;

        case CardStatus::Offline:
            color = Theme::TextSecondary();
            break;
    }

    lv_obj_set_style_bg_color(m_statusDot, color, LV_PART_MAIN);
}
void Card::setAccentColor(lv_color_t color)
{
    if (m_accentBar)
    {
        lv_obj_set_style_bg_color(m_accentBar, color, LV_PART_MAIN);
    }
}
lv_obj_t *Card::root()
{
    return m_root;
}

}