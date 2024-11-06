#include "pch.h"
#include "TextSprite.h"
#include "Texture.h"

TextSprite::TextSprite(const std::string& text, const std::string& fontPath, int fontSize, const Color4f& color)
	: BasicSprite(new Texture{ text, fontPath, fontSize, color }, Point2f{}, 1)
	, m_Text{ text }
	, m_FontPath{ fontPath }
	, m_FontSize{ fontSize }
	, m_Color{ color }
{
}

TextSprite::~TextSprite()
{
	delete m_pTexture;
}

void TextSprite::SetText(const std::string& text)
{
	m_Text = text;
	UpdateTexture();
}

void TextSprite::SetFontSize(int fontSize)
{
	m_FontSize = fontSize;
	UpdateTexture();
}

void TextSprite::SetColor(const Color4f& color)
{
	m_Color = color;
	UpdateTexture();
}

void TextSprite::UpdateTexture()
{
	const Point2f center{ m_DstRect.left + m_DstRect.width / 2, m_DstRect.bottom + m_DstRect.height / 2 };
	delete m_pTexture;
	m_pTexture = new Texture{ m_Text, m_FontPath, m_FontSize, m_Color };
	m_DstRect.width = m_pTexture->GetWidth();
	m_DstRect.height = m_pTexture->GetHeight();
	SetCenter(center);
	SetSrcRect(Rectf{ 0,0, m_DstRect.width, m_DstRect.height });
}