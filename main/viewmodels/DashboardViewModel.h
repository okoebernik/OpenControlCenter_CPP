#pragma once

#include <cstdint>
#include "ViewModel.h"
#include "models/SystemModel.h"

namespace OCC
{

class DashboardViewModel : public ViewModel
{
public:
    explicit DashboardViewModel(SystemModel *systemModel);

    void update() override;

    const char *heapText() const;
    const char *systemPrimaryText() const;
    const char *flashText() const;

private:
    SystemModel *m_systemModel = nullptr;
    char m_heapText[32] = "--- KB";
    char m_systemPrimaryText[32] = "OK";
    char m_flashText[32] = "32 MB";
};

}