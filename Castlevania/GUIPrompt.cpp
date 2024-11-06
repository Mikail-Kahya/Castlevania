#include "pch.h"
#include "GUIPrompt.h"

GUIPrompt::GUIPrompt(const std::string& prompt, const Point2f& pivot)
{
	m_pSprite = GetTextureManager().CreateText(prompt, pivot);
	const float padding{ 10 };
	m_Background.width = m_pSprite->GetWidth() + padding * 2;
	m_Background.height = m_pSprite->GetHeight() + padding;
	m_Background.left = pivot.x - m_Background.width / 2;
	m_Background.bottom = pivot.y - padding / 2;
}

GUIPrompt::~GUIPrompt()
{
	delete m_pSprite;
}

void GUIPrompt::Draw() const
{
	glColor4f(0, 0, 0.1f, 0.7f);
	utils::FillRect(m_Background);
	glColor4f(1, 1, 1, 1);
	m_pSprite->Draw();
}