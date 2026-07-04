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
void DashboardScreen::show()
{
    lv_obj_t *screen = lv_scr_act();
    lv_obj_clean(screen);

    Theme::applyScreen(screen);

    StatusBar statusBar;
    statusBar.create(screen);
    statusBar.update("10:42", "WiFi -", "MQTT -");

    m_navigationBar.create(screen);

    LayoutManager layout(20, 60, 3, 240, 160, 20);

    Card aquarium;
	aquarium.create(screen, "Aquarium");
	aquarium.setAccentColor(lv_color_hex(0x00BCD4));
	aquarium.setStatus(CardStatus::Ok);
	aquarium.setPrimaryValue("24.7", "C");
	aquarium.addValue("pH", "6.8");
	aquarium.addValue("CO2", "23 mg/l");
	layout.add(aquarium);

	Card victron;
	victron.create(screen, "Victron");
	victron.setAccentColor(lv_color_hex(0xFFC107));
    victron.addValue("PV", "3.2 kW");
    victron.addValue("Battery", "82 %");
    victron.addValue("Load", "1.4 kW");
    layout.add(victron);

	Card weather;
	weather.create(screen, "Wetter");
	weather.setAccentColor(lv_color_hex(0x64B5F6));
    weather.addValue("Aussen", "21.3 C");
    weather.addValue("Feuchte", "58 %");
    weather.addValue("Wind", "12 km/h");
    layout.add(weather);

	Card synology;
	synology.create(screen, "Synology");
	synology.setAccentColor(lv_color_hex(0x4CAF50));
    synology.addValue("CPU", "18 %");
    synology.addValue("RAM", "42 %");
    synology.addValue("Storage", "78 %");
    layout.add(synology);

	Card proxmox;
	proxmox.create(screen, "ProxMox");
	proxmox.setAccentColor(lv_color_hex(0x7E57C2));
    proxmox.addValue("Cluster", "OK");
    proxmox.addValue("Nodes", "4/4");
    proxmox.addValue("Backup", "OK");
    layout.add(proxmox);

    SystemCard system;
	system.create(screen);
	layout.add(system.card());
}

void DashboardScreen::update()
{
}

}