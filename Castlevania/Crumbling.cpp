#include "pch.h"
#include "debugPch.h"
#include "Crumbling.h"
#include "Dust.h"

Crumbling::Crumbling(const Point2f& pivot, const Vector2f& velocity, BasicSprite* pSprite)
	: m_pSprite{ pSprite }
{
	Setup(pivot, velocity);
}

Crumbling::~Crumbling()
{
	delete m_pSprite;
}

void Crumbling::Update(float deltaTime)
{
	DynamicParticle::Update(deltaTime);

	m_pSprite->SetPivot(m_RigidBody.GetPivot());
	if (m_RigidBody.IsGrounded())
	{
		GetSoundManager().PlaySound("CrumblingBreak");
		SetExplodeParticle(new Dust{ m_RigidBody.GetPivot() });
	}
}

void Crumbling::Draw() const
{
	m_pSprite->Draw();
#ifdef _DEBUG_PARTICLE
	utils::SetColor(Color4f{ 0.5f, 1, 0.6f, 1 });
	utils::DrawRect(m_RigidBody.GetHurtBox());
#endif
}

void Crumbling::Setup(const Point2f& pivot, const Vector2f& velocity)
{
	m_pSprite->SetPivot(pivot);
	m_RigidBody = RigidBody{ pivot, m_pSprite->GetWidth(), m_pSprite->GetHeight(), velocity };
}