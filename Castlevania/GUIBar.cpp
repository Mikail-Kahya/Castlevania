#include "pch.h"
#include "GUIBar.h"

GUIBar::GUIBar(BasicSprite* pSprite, const Rectf& fullSrcRect)
	: m_pSprite{ pSprite }
	, m_FullSrcRect{ fullSrcRect }
{
}

GUIBar::~GUIBar()
{
	delete m_pSprite;
}

void GUIBar::Draw() const
{
	m_pSprite->Draw();
}

void GUIBar::Update(int stat, float deltaTime)
{
	SetCurrentStat(stat);
	if (!IsChanged()) return;

	const float ratioThreshold{ 0.05f };
	const float ratio{ GetRatio() };
	Rectf srcRect{ m_FullSrcRect };

	if (ratio <= ratioThreshold)
		srcRect.width = 2; // show sliver of bar instead of nothing
	else
		srcRect.width *= ratio;

	m_pSprite->SetSrcRect(srcRect);
}
