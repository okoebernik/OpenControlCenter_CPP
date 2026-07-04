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

private:
    SystemModel *m_systemModel = nullptr;

    char m_heapText[32] = "--- KB";
};

}