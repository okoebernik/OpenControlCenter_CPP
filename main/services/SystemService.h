#pragma once

#include <cstdint>

#include "core/Service.h"
#include "models/SystemModel.h"

namespace OCC
{

class SystemService : public Service
{
public:
    explicit SystemService(SystemModel *model);

    void begin() override;
    void update(uint32_t deltaMs) override;

private:
    SystemModel *m_model = nullptr;
    uint32_t m_elapsedMs = 0;
};

}