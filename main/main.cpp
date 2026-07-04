#include "app/Application.h"

extern "C" void app_main(void)
{
    static OCC::Application app;
    app.run();
}