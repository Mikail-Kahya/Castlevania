#include "pch.h"
#include "Bone.h"
#include "Dust.h"

Bone::Bone(const Point2f& from, const Point2f& to, int damage)
	: ThrowableWeapon(damage, from, to, 1.2f)
{
	m_pSprite = dynamic_cast<BasicSprite*>(GetTextureManager().CreateSprite("bone"));
	m_RigidBody.SetWidth(m_pSprite->GetWidth());
	m_RigidBody.SetHeight(m_pSprite->GetHeight());
}

Bone::~Bone()
{
	OnHit();
}

void Bone::Draw() const
{
	Weapon::Draw();
	m_pSprite->Draw();
}

void Bone::Update(Entity* pOwner, float deltaTime)
{
	ThrowableWeapon::Update(pOwner, deltaTime);
	m_Hitbox = m_RigidBody.GetHurtBox();
	m_pSprite->SetPivot(m_RigidBody.GetPivot());
	Rotate(deltaTime);
	m_AllowDelete = m_RigidBody.IsGrounded();
}

void Bone::OnHit()
{
	GetParticleManager().AddParticle(new Dust(Point2f{ m_Hitbox.left + m_Hitbox.width / 2, m_Hitbox.bottom }));
	GetSoundManager().PlaySound("CrumblingBreak");
}

void Bone::Rotate(float deltaTime) const
{
	const float rotationSpeed{ 720 };
	const float angle{ m_pSprite->GetRotation() + rotationSpeed * deltaTime };
	m_pSprite->SetRotation(angle);
}