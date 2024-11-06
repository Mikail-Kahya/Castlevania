#include "pch.h"
#include "GUIFrame.h"

GUIFrame::GUIFrame(Sprite* pSprite, float opacity)
	: m_pSprite{ pSprite }
	, m_Opacity{ opacity }
{
}

GUIFrame::~GUIFrame()
{
	delete m_pSprite;
}

void GUIFrame::Draw() const
{
	glColor4f(1, 1, 1, m_Opacity);
	m_pSprite->Draw();
	glColor4f(1, 1, 1, 1);
}

float GUIFrame::GetOpacity() const
{
	return m_Opacity;
}
