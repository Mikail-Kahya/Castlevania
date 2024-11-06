#include "pch.h"
#include "Mana.h"
#include "myUtils.h"

Mana::Mana(const Point2f& spawn)
	: m_Origin{ spawn }
{
	Setup(spawn);
}

void Mana::Setup(const Point2f& spawn)
{
	Sprite* pSprite{ GetTextureManager().CreateSprite("mana") };
	SetSprite(pSprite);
	m_pSprite = dynamic_cast<AnimatedSprite*>(pSprite);
	m_RigidBody = RigidBody{ spawn, m_pSprite->GetWidth(), m_pSprite->GetHeight(), Vector2f{} };
}

void Mana::Update(float deltaTime)
{
	PickUp::Update(deltaTime);
	UpdateSprite(deltaTime);
}

bool Mana::Collect()
{
	if (PickUp::Collect())
	{
		GetPlayer()->AddMana(m_ManaIncrease);
		GetSoundManager().PlaySound("ManaPickUp");
		return true;
	}

	return false;
}

void Mana::UpdateRigidBody(float deltaTime)
{
	if (m_RigidBody.IsGrounded()) return;

	UpdateSine(deltaTime);
	m_RigidBody.CollideHard();
	m_RigidBody.CollideSoft();
}

void Mana::UpdateSprite(float deltaTime)
{
	m_pSprite->Update(deltaTime);
	m_pSprite->SetPivot(m_RigidBody.GetPivot());
}

void Mana::UpdateSine(float deltaTime)
{
	Point2f pivot{ m_RigidBody.GetPivot() };
	pivot.y -= m_MoveSpeed * deltaTime;

	const float sineDistance{ abs(m_Origin.y - pivot.y) };
	pivot.x = m_Origin.x + myUtils::CalcSineWave(sineDistance, m_Amplitude, m_PeriodLength);
	
	m_RigidBody.SetPivot(pivot);
}