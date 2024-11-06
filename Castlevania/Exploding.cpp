#include "pch.h"
#include "debugPch.h"
#include "Exploding.h"
#include "Explosion.h"

Exploding::Exploding(const Point2f& pivot, const Vector2f& velocity, BasicSprite* pSprite)
	: m_pSprite{ pSprite }
{
	Setup(pivot, velocity);
}

Exploding::~Exploding()
{
	delete m_pSprite;
}

void Exploding::Setup(const Point2f& pivot, const Vector2f& velocity)
{
	m_pSprite->SetPivot(pivot);
	m_RigidBody = RigidBody{ pivot, m_pSprite->GetWidth(), m_pSprite->GetHeight(), velocity };
}

void Exploding::Update(float deltaTime)
{
	DynamicParticle::Update(deltaTime);
	
	m_pSprite->SetPivot(m_RigidBody.GetPivot());
	if (m_RigidBody.IsGrounded())
	{
		GetSoundManager().PlaySound("PartBreak");
		SetExplodeParticle(new Explosion{ m_RigidBody.GetPivot() });
	}
}

void Exploding::Draw() const
{
	m_pSprite->Draw();
#ifdef _DEBUG_PARTICLE
	utils::SetColor(Color4f{ 0.5f, 1, 0.6f, 1 });
	utils::DrawRect(m_RigidBody.GetHurtBox());
#endif
}