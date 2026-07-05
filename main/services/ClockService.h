#pragma once

#include <cstdint>

#include "core/Service.h"
#include "models/ClockModel.h"
#include "models/WiFiModel.h"

namespace OCC
{

class ClockService : public Service
{
public:
    ClockService(ClockModel *clockModel, WiFiModel *wifiModel);

    void begin() override;
    void update(uint32_t deltaMs) override;

private:
    ClockModel *m_clockModel = nullptr;
    WiFiModel *m_wifiModel = nullptr;

    uint32_t m_elapsedMs = 0;
    uint32_t m_uptimeSeconds = 0;
	bool m_sntpStartRequested = false;

	static void sntpStartTask(void *param);
	
    bool m_sntpStarted = false;

    void startSntp();
    bool isTimeValid() const;
};

}