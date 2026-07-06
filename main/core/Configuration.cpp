#include "Configuration.h"
#include "hardware/PreferencesHardware.h"
#include <cstring>

namespace OCC
{

Configuration &Configuration::instance()
{
    static Configuration config;
    return config;
}

void Configuration::loadDefaults()
{
    setHostname("occ-panel");

    setWifiSsid("");
    setWifiPassword("");

    setMqttBroker("192.168.150.156");
    setMqttPort(1883);

    setDisplayBrightness(100);
}
void Configuration::reset()
{
    loadDefaults();
    save();
}

void Configuration::load()
{
    loadDefaults();

    PreferencesHardware::readString(
        "hostname",
        m_hostname,
        m_hostname,
        sizeof(m_hostname));

    PreferencesHardware::readString(
        "wifi_ssid",
        m_wifiSsid,
        m_wifiSsid,
        sizeof(m_wifiSsid));

    PreferencesHardware::readString(
        "wifi_password",
        m_wifiPassword,
        m_wifiPassword,
        sizeof(m_wifiPassword));

    PreferencesHardware::readString(
        "mqtt_broker",
        m_mqttBroker,
        m_mqttBroker,
        sizeof(m_mqttBroker));

    m_mqttPort =
        PreferencesHardware::readInt(
            "mqtt_port",
            m_mqttPort);

    m_displayBrightness =
        PreferencesHardware::readInt(
            "brightness",
            m_displayBrightness);

	m_initialized =
		PreferencesHardware::readInt(
			"initialized",
			0) != 0;

}

void Configuration::save()
{
    PreferencesHardware::writeString(
        "hostname",
        m_hostname);

    PreferencesHardware::writeString(
        "wifi_ssid",
        m_wifiSsid);

    PreferencesHardware::writeString(
        "wifi_password",
        m_wifiPassword);

    PreferencesHardware::writeString(
        "mqtt_broker",
        m_mqttBroker);

    PreferencesHardware::writeInt(
        "mqtt_port",
        m_mqttPort);

    PreferencesHardware::writeInt(
        "brightness",
        m_displayBrightness);
		
	PreferencesHardware::writeInt(
		"initialized",
		m_initialized ? 1 : 0);

}

bool Configuration::isInitialized() const
{
    return m_initialized;
}

void Configuration::setInitialized(bool value)
{
    m_initialized = value;
}

const char *Configuration::hostname() const
{
    return m_hostname;
}

const char *Configuration::wifiSsid() const
{
    return m_wifiSsid;
}

const char *Configuration::wifiPassword() const
{
    return m_wifiPassword;
}

const char *Configuration::mqttBroker() const
{
    return m_mqttBroker;
}

int Configuration::mqttPort() const
{
    return m_mqttPort;
}

int Configuration::displayBrightness() const
{
    return m_displayBrightness;
}

void Configuration::setHostname(const char *value)
{
    if (!value) return;

    strncpy(m_hostname, value, sizeof(m_hostname));
    m_hostname[sizeof(m_hostname) - 1] = '\0';
}

void Configuration::setWifiSsid(const char *value)
{
    if (!value) return;

    strncpy(m_wifiSsid, value, sizeof(m_wifiSsid));
    m_wifiSsid[sizeof(m_wifiSsid) - 1] = '\0';
}

void Configuration::setWifiPassword(const char *value)
{
    if (!value) return;

    strncpy(m_wifiPassword, value, sizeof(m_wifiPassword));
    m_wifiPassword[sizeof(m_wifiPassword) - 1] = '\0';
}

void Configuration::setMqttBroker(const char *value)
{
    if (!value) return;

    strncpy(m_mqttBroker, value, sizeof(m_mqttBroker));
    m_mqttBroker[sizeof(m_mqttBroker) - 1] = '\0';
}

void Configuration::setMqttPort(int value)
{
    if (value > 0 && value <= 65535)
    {
        m_mqttPort = value;
    }
}

void Configuration::setDisplayBrightness(int value)
{
    if (value < 0) value = 0;
    if (value > 100) value = 100;

    m_displayBrightness = value;
}



}