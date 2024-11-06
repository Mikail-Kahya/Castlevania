#include "pch.h"
#include "DamageNumber.h"
#include "myUtils.h"

DamageNumber::DamageNumber(const Point2f& pivot, int damage, const Color4f& color)
	: FlyingParticle(pivot, Vector2f{})
	, m_pSprite{ GetTextureManager().CreateText(damage, pivot, 12, color) }
{
	const float maxY{ 20 };
	const float maxX{ 10 };
	m_Velocity = Vector2f{ myUtils::GenRand(-maxX, maxX), myUtils::GenRand(maxY) };
}

DamageNumber::~DamageNumber()
{
	delete m_pSprite;
}

void DamageNumber::Update(float deltaTime)
{
	FlyingParticle::Update(deltaTime);
	m_pSprite->SetPivot(m_BottomLeft);

	m_Timer += deltaTime;
	const float maxTime{ 1.5f };
	m_Delete = maxTime < m_Timer;
}

void DamageNumber::Draw() const
{
	DrawBackground();
	m_pSprite->Draw();
}

void DamageNumber::DrawBackground() const
{
	const float padding{ 2 };
	Point2f center{ m_pSprite->GetPosition() };
	const float radX{ m_pSprite->GetWidth() / 2 };
	const float radY{ m_pSprite->GetHeight() / 2 };
	center.y += radY;
	center.x += radX;

	glColor4f(0, 0, 0, 0.5f);
	utils::FillEllipse(center, radX + padding * 2, radY + padding);
	glColor4f(1, 1, 1, 1);
}