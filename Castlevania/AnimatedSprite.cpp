#include "pch.h"
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const Texture* pTexture, const Point2f& bottomLeft, float scale)
	: Sprite(pTexture, bottomLeft, scale)
{
}

AnimatedSprite::AnimatedSprite(const Texture* pTexture, const Anim& animation, const Point2f& bottomLeft, float scale)
	: AnimatedSprite(pTexture, bottomLeft, scale)
{
	SetAnimation(animation);
}

void AnimatedSprite::Update(float elapsedSec)
{
	if (!m_Anim.loop && IsLastFrame()) return;

	m_AccumTime += elapsedSec;
	if (m_AccumTime < m_Anim.frameTime) return;

	if (m_Anim.reverse)
	{
		--m_Anim.currentFrame;
		if (m_Anim.currentFrame == -1)
			m_Anim.currentFrame = m_Anim.nrFrames - 1;
	}
	else
	{
		++m_Anim.currentFrame;
		m_Anim.currentFrame %= m_Anim.nrFrames;
	}

	m_AccumTime -= m_Anim.frameTime;
	m_SrcRect = GetSrcRect();
}

float AnimatedSprite::GetAnimationTime() const
{
	return m_Anim.frameTime * m_Anim.nrFrames;
}

const Anim& AnimatedSprite::GetAnim() const
{
	return m_Anim;
}

int AnimatedSprite::GetRow() const
{
	return m_Anim.currentFrame / m_Anim.cols + 1;
}

void AnimatedSprite::SetAnimation(const Anim& animation)
{
	m_Anim = animation;
	m_DstRect.width = animation.frameWidth * m_Scale;
	m_DstRect.height = animation.frameHeight * m_Scale;
	m_SrcRect = GetSrcRect();
}

void AnimatedSprite::SetReverse(bool isReversing)
{
	m_Anim.reverse = isReversing;
	if (isReversing && m_Anim.currentFrame == 0)
		m_Anim.currentFrame = m_Anim.nrFrames - 1;
}

void AnimatedSprite::FullReverse()
{
	if (m_Anim.reverse)
		m_Anim.currentFrame = 0;
	else
		m_Anim.currentFrame = m_Anim.nrFrames - 1;
	m_Anim.reverse = !m_Anim.reverse;
}

int AnimatedSprite::GetCol() const
{
	return m_Anim.currentFrame % m_Anim.cols;
}

const Rectf AnimatedSprite::GetSrcRect() const
{
	const float x{ m_Anim.startPos.x + m_Anim.frameWidth * GetCol() };
	const float y{ m_Anim.startPos.y + m_Anim.frameHeight * GetRow() };
	const float width{ m_Anim.frameWidth };
	const float height{ m_Anim.frameHeight };

	return Rectf{ x, y, width, height };
}

bool AnimatedSprite::IsLastFrame() const
{
	if (m_Anim.reverse)
		return m_Anim.currentFrame == 0;
	else
		return m_Anim.currentFrame == m_Anim.nrFrames - 1;
}

bool AnimatedSprite::IsReversed() const
{
	return m_Anim.reverse;
}