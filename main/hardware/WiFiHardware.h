#pragma once

namespace OCC
{

class WiFiHardware
{
public:
    static void begin();
    static void connect(const char *ssid, const char *password);
    static bool isConnected();
	static void getIpText(char *buffer, int bufferSize);
};

}