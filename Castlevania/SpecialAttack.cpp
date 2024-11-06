#include "pch.h"
#include "SpecialAttack.h"
#include "Sparkle.h"
#include "myUtils.h"

SpecialAttack::SpecialAttack(Entity* pOwner)
	: Weapon(60)
{
	const Rectf hurtBox{ pOwner->GetHurtBox() };
	const float widthScale{ 20 }, heightScale{ 2 };
	m_Hitbox = Rectf{ 0, 0, hurtBox.width * widthScale, hurtBox.height * heightScale };
}

void SpecialAttack::Update(Entity* pOwner, float deltaTime)
{
	Weapon::Update(pOwner, deltaTime);
	if (!m_IsActive) return;
	Reposition(pOwner);
	SpawnParticles();
}

void SpecialAttack::Reposition(Entity* pOwner)
{
	const Rectf hurtBox{ pOwner->GetHurtBox() };
	Point2f bottomLeft{ hurtBox.left + hurtBox.width,
							hurtBox.bottom + hurtBox.height / 2 - m_Hitbox.height / 2 };
	if (IsFlipped(pOwner))
		bottomLeft.x -= hurtBox.width + m_Hitbox.width;

	SetBottomLeft(bottomLeft);
}

void SpecialAttack::SpawnParticles()
{
	GetParticleManager().AddParticle(new Sparkle{ myUtils::GetRandPointInRect(m_Hitbox) });
}
