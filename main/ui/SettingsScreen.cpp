#include "SettingsScreen.h"
#include "Theme.h"
#include "StatusBar.h"
#include "NavigationBar.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"

namespace OCC
{

static constexpr int SettingsTopY = 80;
static constexpr int SettingsCardHeight = 160;
static constexpr int SettingsGap = 20;

static constexpr int SystemCardX = 20;
static constexpr int SystemCardWidth = 240;
static constexpr int SystemRowWidth = 200;

static constexpr int NetworkCardX = SystemCardX + SystemCardWidth + SettingsGap;
static constexpr int NetworkCardWidth = 310;
static constexpr int NetworkRowWidth = 270;	
	
static constexpr int BrightnessButtonWidth = 54;
static constexpr int BrightnessButtonHeight = 30;

SettingsScreen::SettingsScreen(EventBus *eventBus)
    : m_eventBus(eventBus),
	  m_navigationBar(eventBus)
{
}
void SettingsScreen::create(lv_obj_t *parent)
{
    m_root = lv_obj_create(parent);
    lv_obj_set_size(m_root, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_border_width(m_root, 0, LV_PART_MAIN);
    lv_obj_clear_flag(m_root, LV_OBJ_FLAG_SCROLLABLE);

    Theme::applyScreen(m_root);

	m_statusBar.create(m_root);
	m_statusBar.update("00:00", "WiFi -", "MQTT -");

    m_navigationBar.create(m_root);

	m_systemSettingsCard.create(m_root, "System");
	m_systemSettingsCard.setPosition(SystemCardX, SettingsTopY);
	m_systemSettingsCard.setSize(SystemCardWidth, SettingsCardHeight);

	m_hostnameRow = m_systemSettingsCard.addMetric("Hostname", "---");
	m_hostnameRow->setWidth(SystemRowWidth);
	
	m_brightnessRow = m_systemSettingsCard.addMetric("Brightness", "---");
	m_brightnessRow->setWidth(SystemRowWidth);
	
	m_brightnessMinusButton.create(m_root, "-");
	m_brightnessMinusButton.setCallback(onBrightnessMinus, this);
	m_brightnessMinusButton.setSize(
		BrightnessButtonWidth,
		BrightnessButtonHeight);

	m_brightnessMinusButton.setPosition(95, 205);

	m_brightnessPlusButton.create(m_root, "+");
	m_brightnessPlusButton.setCallback(onBrightnessPlus, this);
	m_brightnessPlusButton.setSize(
		BrightnessButtonWidth,
		BrightnessButtonHeight);

	m_brightnessPlusButton.setPosition(155, 205);
	
	m_networkSettingsCard.create(m_root, "Network");
	m_networkSettingsCard.setPosition(NetworkCardX, SettingsTopY);
	m_networkSettingsCard.setSize(NetworkCardWidth, SettingsCardHeight);
	
	m_wifiSsidRow = m_networkSettingsCard.addMetric("WiFi SSID", "---");
	m_wifiSsidRow->setWidth(NetworkRowWidth);
	
	m_mqttBrokerRow = m_networkSettingsCard.addMetric("MQTT Broker", "---");
	m_mqttBrokerRow->setWidth(NetworkRowWidth);

}

void SettingsScreen::show()
{
    if (m_root)
    {
        lv_obj_clear_flag(m_root, LV_OBJ_FLAG_HIDDEN);
    }
}

void SettingsScreen::setViewModel(SettingsViewModel *viewModel)
{
    m_viewModel = viewModel;
}

void SettingsScreen::hide()
{
    if (m_root)
    {
        lv_obj_add_flag(m_root, LV_OBJ_FLAG_HIDDEN);
    }
}
void SettingsScreen::setStatusBarViewModel(StatusBarViewModel *viewModel)
{
    m_statusBarViewModel = viewModel;
}

void SettingsScreen::onBrightnessMinus(void *userData)
{
    auto *screen = static_cast<SettingsScreen *>(userData);

    if (screen && screen->m_eventBus)
    {
        screen->m_eventBus->publish({
            EventType::BrightnessDecrease,
            ScreenId::Settings,
            0
        });
    }
}

void SettingsScreen::onBrightnessPlus(void *userData)
{
    auto *screen = static_cast<SettingsScreen *>(userData);

    if (screen && screen->m_eventBus)
    {
        screen->m_eventBus->publish({
            EventType::BrightnessIncrease,
            ScreenId::Settings,
            0
        });
    }
}

void SettingsScreen::update()
{
    static TickType_t lastTick = 0;
    TickType_t now = xTaskGetTickCount();

    if ((now - lastTick) < pdMS_TO_TICKS(250))
    {
        return;
    }

    lastTick = now;

    if (m_statusBarViewModel)
    {
        m_statusBarViewModel->update();
        m_statusBar.update(*m_statusBarViewModel);
    }

    if (m_viewModel)
    {
        m_viewModel->update();

        if (m_hostnameRow) m_hostnameRow->setValue(m_viewModel->hostnameText());
        if (m_brightnessRow) m_brightnessRow->setValue(m_viewModel->brightnessText());
        if (m_wifiSsidRow) m_wifiSsidRow->setValue(m_viewModel->wifiSsidText());
        if (m_mqttBrokerRow) m_mqttBrokerRow->setValue(m_viewModel->mqttBrokerText());
    }
}
}