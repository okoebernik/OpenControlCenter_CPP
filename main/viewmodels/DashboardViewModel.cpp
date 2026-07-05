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

    snprintf(
        m_systemPrimaryText,
        sizeof(m_systemPrimaryText),
        "OK"
    );

    snprintf(
        m_flashText,
        sizeof(m_flashText),
        "32 MB"
    );
	
}

const char *DashboardViewModel::heapText() const
{
    return m_heapText;
}

const char *DashboardViewModel::systemPrimaryText() const
{
    return m_systemPrimaryText;
}

const char *DashboardViewModel::flashText() const
{
    return m_flashText;
}
}