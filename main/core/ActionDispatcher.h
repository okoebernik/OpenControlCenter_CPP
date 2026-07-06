#pragma once

#include "core/UIAction.h"

namespace OCC
{

class ActionDispatcher
{
public:
    using Handler = void (*)(UIAction action, void *userData);

    void setHandler(Handler handler, void *userData);
    void dispatch(UIAction action);

private:
    Handler m_handler = nullptr;
    void *m_userData = nullptr;
};

}