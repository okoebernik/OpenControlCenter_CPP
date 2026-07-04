#include "DashboardViewModel.h"

#include <cstdio>

namespace OCC
{

DashboardViewModel::DashboardViewModel(SystemModel *systemModel, ClockModel *clockModel)
    : m_systemModel(systemModel),
      m_clockModel(clockModel)
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
	
	if (m_clockModel)
	{
		uint32_t seconds = m_clockModel->seconds();

		uint32_t minutes = (seconds / 60) % 60;
		uint32_t hours = (seconds / 3600) % 24;

		snprintf(
			m_clockText,
			sizeof(m_clockText),
			"%02lu:%02lu",
			static_cast<unsigned long>(hours),
			static_cast<unsigned long>(minutes)
    );
}
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
const char *DashboardViewModel::clockText() const
{
    return m_clockText;
}
}