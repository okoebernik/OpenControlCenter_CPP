#include "IconButton.h"
#include "Theme.h"

namespace OCC
{

void IconButton::create(lv_obj_t *parent, const char *text)
{
    m_root = lv_btn_create(parent);
    lv_obj_set_size(m_root, 44, 36);
    lv_obj_clear_flag(m_root, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_bg_color(m_root, Theme::SurfaceAlt(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(m_root, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_radius(m_root, 8, LV_PART_MAIN);
    lv_obj_set_style_border_width(m_root, 0, LV_PART_MAIN);

    m_label = lv_label_create(m_root);
    lv_label_set_text(m_label, text);
    lv_obj_set_style_text_color(m_label, Theme::TextPrimary(), LV_PART_MAIN);
    lv_obj_center(m_label);

    lv_obj_add_event_cb(m_root, onClicked, LV_EVENT_CLICKED, this);
}

void IconButton::setPosition(int x, int y)
{
    if (m_root)
    {
        lv_obj_set_pos(m_root, x, y);
    }
}

void IconButton::setSize(int width, int height)
{
    if (m_root)
    {
        lv_obj_set_size(m_root, width, height);
    }
}

void IconButton::setText(const char *text)
{
    if (m_label && text)
    {
        lv_label_set_text(m_label, text);
        lv_obj_center(m_label);
    }
}

void IconButton::setCallback(ClickCallback callback, void *userData)
{
    m_callback = callback;
    m_userData = userData;
}

lv_obj_t *IconButton::root()
{
    return m_root;
}

void IconButton::onClicked(lv_event_t *event)
{
    auto *button = static_cast<IconButton *>(lv_event_get_user_data(event));

    if (button && button->m_callback)
    {
        button->m_callback(button->m_userData);
    }
	
	if (button->m_dispatcher)
	{
		button->m_dispatcher->dispatch(button->m_action);
	}
	
}
void IconButton::setAction(ActionDispatcher *dispatcher, UIAction action)
{
    m_dispatcher = dispatcher;
    m_action = action;
}
}