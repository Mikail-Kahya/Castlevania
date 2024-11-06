#include "pch.h"
#include "debugPch.h"
#include "Weapon.h"
#include "Entity.h"

Weapon::Weapon(int damage)
	: m_Damage{ damage }
{
}

void Weapon::Draw() const
{
#ifdef _DEBUG_COMBAT
	glColor4f(1, 0, 0, 1);
	utils::DrawRect(m_Hitbox);
	glColor4f(1, 1, 1, 1);
#endif
}

void Weapon::Update(Entity* pOwner, float deltaTime)
{
	if (m_UseDelayTimer > 0)
		m_UseDelayTimer -= deltaTime;
}

bool Weapon::Use(float delay)
{
	if (m_UseDelayTimer <= 0)
	{
		m_IsActive = true;
		m_UseDelayTimer = delay;
		return true;
	}
	return false;
}

void Weapon::Disable()
{
	m_IsActive = false;
}

const Rectf& Weapon::GetHitbox() const
{
	return m_Hitbox;
}

int Weapon::GetDamage() const
{
	return m_Damage;
}

bool Weapon::IsActive() const
{
	return m_IsActive;
}

void Weapon::SetBottomLeft(const Point2f& bottomLeft)
{
	m_Hitbox.left = bottomLeft.x;
	m_Hitbox.bottom = bottomLeft.y;
}

bool Weapon::IsFlipped(Entity* pOwner)
{
	return pOwner->m_pSprite->IsFlipped();
}
