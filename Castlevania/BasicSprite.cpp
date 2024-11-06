#include "pch.h"
#include "BasicSprite.h"
#include "Texture.h"

BasicSprite::BasicSprite(const Texture* pTexture, const Point2f& bottomLeft, float scale)
	: Sprite(pTexture, bottomLeft, scale)
{
	SetSrcRect(Rectf{ 0,0, pTexture->GetWidth(), pTexture->GetHeight() });
}

void BasicSprite::SetSrcRect(const Rectf& srcRect)
{
	m_SrcRect = srcRect;
	m_DstRect.width = m_SrcRect.width * m_Scale;
	m_DstRect.height = m_SrcRect.height * m_Scale;
}