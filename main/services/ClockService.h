#pragma once

#include <cstdint>

#include "core/Service.h"
#include "models/ClockModel.h"

namespace OCC
{

class ClockService : public Service
{
public:
    explicit ClockService(ClockModel *model);

    void begin() override;
    void update(uint32_t deltaMs) override;

private:
    ClockModel *m_model = nullptr;
    uint32_t m_elapsedMs = 0;
    uint32_t m_seconds = 0;
	bool m_sntpStarted = false;

	void startSntp();
	bool isTimeValid() const;
};

}