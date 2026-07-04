#pragma once

#include <cstdint>
#include "ViewModel.h"
#include "models/SystemModel.h"
#include "models/ClockModel.h"

namespace OCC
{

class DashboardViewModel : public ViewModel
{
public:
    explicit DashboardViewModel(SystemModel *systemModel, ClockModel *clockModel);

    void update() override;

    const char *heapText() const;
    const char *systemPrimaryText() const;
    const char *flashText() const;
	const char *clockText() const;

private:
    SystemModel *m_systemModel = nullptr;
	ClockModel *m_clockModel = nullptr;
	char m_clockText[16] = "00:00";
    char m_heapText[32] = "--- KB";
    char m_systemPrimaryText[32] = "OK";
    char m_flashText[32] = "32 MB";
};

}