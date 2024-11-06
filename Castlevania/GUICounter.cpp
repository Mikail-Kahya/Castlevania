#include "pch.h"
#include "GUICounter.h"

GUICounter::GUICounter(const Point2f& pivot)
{
	const int fontSize{ 35 };
	m_pSprite = GetTextureManager().CreateText("0", pivot, fontSize);
}

GUICounter::~GUICounter()
{
	delete m_pSprite;
}

void GUICounter::Draw() const
{
	m_pSprite->Draw();
}

void GUICounter::Update(int stat, float deltaTime)
{
	SetCurrentStat(stat);
	if (IsChanged())
		m_pSprite->SetText(std::to_string(stat));
}