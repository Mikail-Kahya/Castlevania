#include "pch.h"
#include "LevelCalculator.h"

LevelCalculator::LevelCalculator(int exp)
	: m_Exp{ exp }
{
	operator()(0);
}

bool LevelCalculator::operator()(int exp)
{
	const int oldLevel{ m_Level };
	m_Exp += exp;
	GetLevel();
	const bool leveledUp{ m_Level != oldLevel };

	return leveledUp;
}

int LevelCalculator::operator()() const
{
	return m_Level;
}

int LevelCalculator::GetLevel()
{
	// Linear growth
	// level function: Exp = base + growthRate * Level
	const int currentLevel{ m_Level };
	m_Level = m_Exp / (BASE + GROWTH);

	return m_Level - currentLevel;
}

int LevelCalculator::GetExpForLevel(int level)
{
	return BASE + GROWTH * level;
}
