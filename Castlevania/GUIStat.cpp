#include "pch.h"
#include "GUIStat.h"

GUIStat::GUIStat()
	: GUIStat(0, 0)
{
}

GUIStat::GUIStat(int maxStat, int currentStat)
	: m_MaxStat{ maxStat }
	, m_CurrentStat{ currentStat }
{
}

void GUIStat::SetMaxStat(int maxStat)
{
	m_MaxStat = maxStat;
}


void GUIStat::SetCurrentStat(int currentStat)
{
	m_StatChanged = m_CurrentStat != currentStat;
	m_CurrentStat = currentStat;
}

float GUIStat::GetRatio() const
{
	return float(m_CurrentStat) / m_MaxStat;
}

bool GUIStat::IsChanged() const
{
	return m_StatChanged;
}