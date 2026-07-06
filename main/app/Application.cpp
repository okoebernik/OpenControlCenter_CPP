#include "Application.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "lvgl.h"
#include "core/Configuration.h"
#include "bsp/esp-bsp.h"
#include "bsp/display.h"

namespace OCC
{

static const char *TAG = "Application";

void Application::initialize()
		
{
	Configuration::instance().load();
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
	bsp_display_brightness_set(Configuration::instance().displayBrightness());
}

void Application::run()
{
    initialize();

    registerScreens();
    registerEvents();

    if (bsp_display_lock(1000))
    {
        m_screenManager.create(lv_scr_act());
        m_screenManager.show(ScreenId::Dashboard);
        bsp_display_unlock();
    }

    m_serviceManager.add(&m_systemService);
    m_serviceManager.add(&m_clockService);
    m_serviceManager.add(&m_wifiService);
    m_serviceManager.begin();

    while (true)
    {
        m_serviceManager.update();

        if (bsp_display_lock(50))
        {
            m_screenManager.update();
            processPendingNavigation();
            bsp_display_unlock();
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void Application::registerScreens()
{
    m_dashboardScreen.setViewModel(&m_dashboardViewModel);
    m_dashboardScreen.setStatusBarViewModel(&m_statusBarViewModel);

    m_settingsScreen.setStatusBarViewModel(&m_statusBarViewModel);
	
	m_settingsScreen.setViewModel(&m_settingsViewModel);
	
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
			 break;
		
		case EventType::BrightnessDecrease:
			app->m_settingsViewModel.decreaseBrightness();
			bsp_display_brightness_set(Configuration::instance().displayBrightness());
			break;

		case EventType::BrightnessIncrease:
			app->m_settingsViewModel.increaseBrightness();
			bsp_display_brightness_set(Configuration::instance().displayBrightness());
			break;
		
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