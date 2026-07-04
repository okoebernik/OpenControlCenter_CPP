#include "DashboardViewModel.h"

#include <cstdio>

namespace OCC
{

DashboardViewModel::DashboardViewModel(SystemModel *systemModel)
    : m_systemModel(systemModel)
{
}

void DashboardViewModel::update()
{
    if (!m_systemModel)
    {
        return;
    }

    snprintf(
        m_heapText,
        sizeof(m_heapText),
        "%lu KB",
        static_cast<unsigned long>(m_systemModel->heap() / 1024)
    );
}

const char *DashboardViewModel::heapText() const
{
    return m_heapText;
}

}