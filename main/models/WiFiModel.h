#pragma once

namespace OCC
{

class WiFiModel
{
public:
    void setConnected(bool connected);
    bool connected() const;

    void setIpText(const char *text);
    const char *ipText() const;

private:
    bool m_connected = false;
    char m_ipText[32] = "0.0.0.0";
};

}