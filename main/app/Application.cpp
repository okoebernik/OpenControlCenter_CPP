#include "Application.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "lvgl.h"

#include "bsp/esp-bsp.h"
#include "bsp/display.h"

namespace OCC
{

static const char *TAG = "Application";

void Application::initialize()
{
    ESP_LOGI(TAG, "Initializing OpenControlCenter");

    bsp_display_cfg_t cfg =
    {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = BSP_LCD_DRAW_BUFF_SIZE,
        .double_buffer = BSP_LCD_DRAW_BUFF_DOUBLE,
        .flags =
        {
            .buff_dma = false,
            .buff_spiram = true,
            .sw_rotate = false
        }
    };

    bsp_display_start_with_config(&cfg);
    bsp_display_backlight_on();
}

void Application::run()
{
    initialize();

    registerScreens();
	registerEvents();
	
	m_serviceManager.add(&m_systemService);
	m_serviceManager.begin();
    m_screenManager.show(ScreenId::Dashboard);

    while (true)
{
    m_serviceManager.update();
    m_screenManager.update();

    lv_task_handler();

    processPendingNavigation();

    vTaskDelay(pdMS_TO_TICKS(5));
}
}

void Application::registerScreens()
{
    m_screenManager.registerScreen(ScreenId::Dashboard, &m_dashboardScreen);
    m_screenManager.registerScreen(ScreenId::Settings, &m_settingsScreen);
}
void Application::registerEvents()
{
    m_eventBus.subscribe(handleEvent, this);
}

void Application::handleEvent(const Event &event, void *userData)
{
    auto *app = static_cast<Application *>(userData);

    if (!app)
    {
        return;
    }

    switch (event.type)
    {
        case EventType::NavigateToScreen:
			 app->m_pendingScreen = event.screenId;
			 app->m_hasPendingScreen = true;
			 break;;

        default:
            break;
    }
}
void Application::processPendingNavigation()
{
    if (!m_hasPendingScreen)
    {
        return;
    }

    m_screenManager.show(m_pendingScreen);
    m_hasPendingScreen = false;
}
}