#include "pch.h"
#include "ThrowableWeapon.h"
#include "Entity.h"
#include "utils.h"

ThrowableWeapon::ThrowableWeapon(int damage, const Point2f& from, const Point2f& to, float throwTime)
	: Weapon(damage)
{
	// velocity calculation
	// s = v_0 t + 1/2 g t^2 ====> v_0 = s/t - 1/2 g t
	const Vector2f displacement{ from, to };
	const float velocityX{ displacement.x / throwTime };
	const float velocityY{ -displacement.y + displacement.y / throwTime - RigidBody::GRAVITY.y / 2 * throwTime };

	m_RigidBody = RigidBody{ from, 0, 0, Vector2f{velocityX, velocityY} };
}

void ThrowableWeapon::Update(Entity* pOwner, float deltaTime)
{
	Weapon::Update(pOwner, deltaTime);
	m_RigidBody.UpdatePhysics(deltaTime);
	if (GetPlayer()->Hurt(m_Hitbox, m_Damage))
		OnHit();

	Collision();
}

bool ThrowableWeapon::Collision()
{
	m_RigidBody.CollideHard();
	return m_RigidBody.IsGrounded();
}

bool ThrowableWeapon::IsGrounded() const
{
	return m_RigidBody.IsGrounded();
}

bool ThrowableWeapon::AllowDelete() const
{
	return m_AllowDelete;
}

void ThrowableWeapon::SetHitBox(float width, float height)
{
	m_RigidBody.SetWidth(width);
	m_RigidBody.SetHeight(height);
}