#include "pch.h"
#include "Dust.h"
#include "myUtils.h"

Dust::Dust(const Point2f& pivot, float scale)
{
	Setup(pivot, scale);
}

Dust::~Dust()
{
	delete m_pSprite;
}

void Dust::Setup(const Point2f& pivot, float scale)
{
	m_pSprite = dynamic_cast<AnimatedSprite*>(GetTextureManager().CreateSprite("dust"));
	m_pSprite->SetPivot(Point2f{ pivot.x, pivot.y - m_pSprite->GetHeight() / 3 });
	m_pSprite->SetFlip(myUtils::GenRand(1));

	const float epsilon{ 0.05f };
	if (scale > epsilon)
		m_pSprite->SetScale(scale);
}

void Dust::Update(float deltaTime)
{
	m_pSprite->Update(deltaTime);
	m_Delete = m_pSprite->IsLastFrame();
}

void Dust::Draw() const
{
	m_pSprite->Draw();
}
