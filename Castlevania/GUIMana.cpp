#include "pch.h"
#include "GUIMana.h"
#include "BasicSprite.h"
#include "myUtils.h"

GUIMana::GUIMana(BasicSprite* pSprite)
	: m_pSprite{ pSprite }
{
}

GUIMana::~GUIMana()
{
	delete m_pSprite;
}

void GUIMana::Draw() const
{
	glColor4f(1, 1, 1, m_Opacity);
	m_pSprite->Draw();
	glColor4f(1, 1, 1, 1);
}

void GUIMana::Update(int stat, float deltaTime)
{
	SetCurrentStat(stat);

	if (GetRatio() >= 1)
	{
		UpdateOpacity(deltaTime);
	}
	else
	{
		m_Timer = 0;
		m_Opacity = 0;
	}
}

void GUIMana::UpdateOpacity(float deltaTime)
{
	const float cycleTime{ 0.5f };
	if (m_Timer > cycleTime)
		m_Timer -= cycleTime;
	else
		m_Timer += deltaTime;

	// use sine wave for easing effect
	m_Opacity = myUtils::CalcSineWave(m_Timer, 1, cycleTime * 2);
}
