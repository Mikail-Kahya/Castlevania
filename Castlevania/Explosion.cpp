#include "pch.h"
#include "Explosion.h"
#include "myUtils.h"

Explosion::Explosion(const Point2f& pivot)
{
	Setup(pivot);
}

Explosion::~Explosion()
{
	delete m_pSprite;
}

void Explosion::Setup(const Point2f& pivot)
{
	m_pSprite = dynamic_cast<AnimatedSprite*>(GetTextureManager().CreateSprite("explosion"));
	m_pSprite->SetPivot(Point2f{ pivot.x, pivot.y - m_pSprite->GetHeight() / 3 });
	m_pSprite->SetFlip(myUtils::GenRand(1));
}

void Explosion::Update(float deltaTime)
{
	m_pSprite->Update(deltaTime);
	m_Delete = m_pSprite->IsLastFrame();
}

void Explosion::Draw() const
{
	m_pSprite->Draw();
}