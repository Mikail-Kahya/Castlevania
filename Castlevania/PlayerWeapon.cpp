#include "pch.h"
#include "PlayerWeapon.h"
#include "Entity.h"
#include "InAttackState.h"

PlayerWeapon::PlayerWeapon(int damage)
	: Weapon(damage)
{
}

PlayerWeapon::~PlayerWeapon()
{
	delete m_pSprite;
}

void PlayerWeapon::Draw() const
{
	Weapon::Draw(); // draw collisions if true
	m_pSprite->Draw();
}

void PlayerWeapon::Update(Entity* pOwner, float deltaTime)
{
	Weapon::Update(pOwner, deltaTime);
	if (!m_IsActive) return;

	// Repositioning weapon based on attack state
	Point2f bottomLeft{ pOwner->GetPivot() };
	const Point2f offset{ GetOffset() };

	if (IsFlipped(pOwner))
	{
		// move weapon to left of player
		m_pSprite->SetFlip(true);
		bottomLeft.x -= m_Hitbox.width + offset.x;
	}
	else
	{
		m_pSprite->SetFlip(false);
		bottomLeft.x += offset.x;
	}
	bottomLeft.y += offset.y;

	m_Hitbox = bottomLeft;
	m_pSprite->SetPosition(bottomLeft);
}

void PlayerWeapon::SetSprite(BasicSprite* pSprite)
{
	m_pSprite = pSprite;
}

void PlayerWeapon::SetOffset(const Point2f& offset, State offsetState)
{
	m_OffsetArr[int(offsetState)] = offset;
}

const Point2f& PlayerWeapon::GetOffset() const
{
	if (GetPlayer()->IsCrouched())
	{
		return m_OffsetArr[int(State::crouched)];
	}
	else if (!GetPlayer()->IsGrounded())
	{
		return m_OffsetArr[int(State::air)];
	}

	return m_OffsetArr[int(State::standing)];
}
