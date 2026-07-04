#include "DashboardScreen.h"
#include "Theme.h"
#include "StatusBar.h"
#include "NavigationBar.h"
#include "Card.h"
#include "LayoutManager.h"
#include "SystemCard.h"

namespace OCC
{
DashboardScreen::DashboardScreen(EventBus *eventBus)
    : m_eventBus(eventBus),
	  m_navigationBar(eventBus)
{
}
void DashboardScreen::setViewModel(DashboardViewModel *viewModel)
{
    m_viewModel = viewModel;
}
void DashboardScreen::create(lv_obj_t *parent)
{
    m_root = lv_obj_create(parent);
    lv_obj_set_size(m_root, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_border_width(m_root, 0, LV_PART_MAIN);
    lv_obj_clear_flag(m_root, LV_OBJ_FLAG_SCROLLABLE);

    Theme::applyScreen(m_root);

    m_statusBar.create(m_root);
	m_statusBar.update("00:00", "WiFi -", "MQTT -");

    m_navigationBar.create(m_root);

    LayoutManager layout(20, 60, 3, 240, 160, 20);

	m_aquariumCard.create(m_root, "Aquarium");
	m_aquariumCard.setAccentColor(lv_color_hex(0x00BCD4));
	m_aquariumCard.setStatus(CardStatus::Ok);
	m_aquariumCard.setPrimaryValue("24.7", "C");
	m_aquariumCard.addValue("pH", "6.8");
	m_aquariumCard.addValue("CO2", "23 mg/l");
	layout.add(m_aquariumCard);

    m_victronCard.create(m_root, "Victron");
    m_victronCard.setAccentColor(lv_color_hex(0xFFC107));
    m_victronCard.setStatus(CardStatus::Ok);
    m_victronCard.addValue("PV", "3.2 kW");
    m_victronCard.addValue("Battery", "82 %");
    m_victronCard.addValue("Load", "1.4 kW");
    layout.add(m_victronCard);

    m_weatherCard.create(m_root, "Wetter");
    m_weatherCard.setAccentColor(lv_color_hex(0x64B5F6));
    m_weatherCard.setStatus(CardStatus::Warning);
    m_weatherCard.addValue("Aussen", "21.3 C");
    m_weatherCard.addValue("Feuchte", "58 %");
    m_weatherCard.addValue("Wind", "12 km/h");
    layout.add(m_weatherCard);

    m_synologyCard.create(m_root, "Synology");
    m_synologyCard.setAccentColor(lv_color_hex(0x4CAF50));
    m_synologyCard.setStatus(CardStatus::Ok);
    m_synologyCard.addValue("CPU", "18 %");
    m_synologyCard.addValue("RAM", "42 %");
    m_synologyCard.addValue("Storage", "78 %");
    layout.add(m_synologyCard);

    m_proxmoxCard.create(m_root, "Proxmox");
    m_proxmoxCard.setAccentColor(lv_color_hex(0x7E57C2));
    m_proxmoxCard.setStatus(CardStatus::Ok);
    m_proxmoxCard.addValue("Cluster", "OK");
    m_proxmoxCard.addValue("Nodes", "4/4");
    m_proxmoxCard.addValue("Backup", "OK");
    layout.add(m_proxmoxCard);

    m_systemCard.create(m_root);
    layout.add(m_systemCard.card());
}

void DashboardScreen::show()
{
    if (m_root)
    {
        lv_obj_clear_flag(m_root, LV_OBJ_FLAG_HIDDEN);
    }
}

void DashboardScreen::hide()
{
    if (m_root)
    {
        lv_obj_add_flag(m_root, LV_OBJ_FLAG_HIDDEN);
    }
}
void DashboardScreen::update()
{
    if (!m_viewModel)
    {
        return;
    }

    m_viewModel->update();

    m_statusBar.update(*m_viewModel);

    m_systemCard.update(*m_viewModel);
}
}