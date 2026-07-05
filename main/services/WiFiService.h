#pragma once

#include <cstdint>

#include "core/Service.h"
#include "models/WiFiModel.h"

namespace OCC
{

class WiFiService : public Service
{
public:
    explicit WiFiService(WiFiModel *model);

    void begin() override;
    void update(uint32_t deltaMs) override;

private:
    WiFiModel *m_model = nullptr;
};

}