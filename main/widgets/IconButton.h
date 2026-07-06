#pragma once

#include "core/ActionDispatcher.h"
#include "core/UIAction.h"
#include "lvgl.h"

namespace OCC
{

class IconButton
{
public:
    using ClickCallback = void (*)(void *userData);

    void create(lv_obj_t *parent, const char *text);

    void setPosition(int x, int y);
    void setSize(int width, int height);
    void setText(const char *text);
    void setCallback(ClickCallback callback, void *userData);
	
	void setAction(ActionDispatcher *dispatcher, UIAction action);

    lv_obj_t *root();

private:
    static void onClicked(lv_event_t *event);

    lv_obj_t *m_root = nullptr;
    lv_obj_t *m_label = nullptr;

    ClickCallback m_callback = nullptr;
    void *m_userData = nullptr;
	
	ActionDispatcher *m_dispatcher = nullptr;
	UIAction m_action = UIAction::None;
};

}