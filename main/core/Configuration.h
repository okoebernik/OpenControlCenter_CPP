#pragma once

namespace OCC
{

class Configuration
{
public:
    static Configuration &instance();
	
	void loadDefaults();
	void load();
	void save();
	void reset();
	
	bool isInitialized() const;
	void setInitialized(bool value);
    
	const char *hostname() const;
    const char *wifiSsid() const;
    const char *wifiPassword() const;
    const char *mqttBroker() const;
    int mqttPort() const;
    int displayBrightness() const;

    void setHostname(const char *value);
    void setWifiSsid(const char *value);
    void setWifiPassword(const char *value);
    void setMqttBroker(const char *value);
    void setMqttPort(int value);
    void setDisplayBrightness(int value);


private:
    Configuration() = default;
	
	bool m_initialized = false;
	
    char m_hostname[32] = "occ-panel";
    char m_wifiSsid[32] = "";
    char m_wifiPassword[64] = "";
    char m_mqttBroker[64] = "192.168.150.1";
    int m_mqttPort = 1883;
    int m_displayBrightness = 100;
};

}