#include "pch.h"
#include "BloodSplatter.h"

BloodSplatter::BloodSplatter(const Point2f& bottomLeft)
{
	m_pSprite = dynamic_cast<AnimatedSprite*>(GetTextureManager().CreateSprite("bloodSplatter", bottomLeft));
	GetSoundManager().PlaySound("BloodSpray");
}

BloodSplatter::~BloodSplatter()
{
	delete m_pSprite;
}

void BloodSplatter::Update(float deltaTime)
{
	m_pSprite->Update(deltaTime);
	m_Delete = m_pSprite->IsLastFrame();
}

void BloodSplatter::Draw() const
{
	m_pSprite->Draw();
}

void BloodSplatter::Flip() const
{
	m_pSprite->SetFlip(true);
	Point2f bottomLeft{ m_pSprite->GetPosition() };
	bottomLeft.x -= m_pSprite->GetWidth();
	m_pSprite->SetPosition(bottomLeft);
}