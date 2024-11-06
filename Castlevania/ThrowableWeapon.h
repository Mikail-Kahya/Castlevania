#pragma once
#include "Weapon.h"
#include "RigidBody.h"

class ThrowableWeapon : public Weapon
{
public:
	virtual ~ThrowableWeapon() = default;

	ThrowableWeapon(const ThrowableWeapon& other) = delete;
	ThrowableWeapon& operator=(const ThrowableWeapon& other) = delete;
	ThrowableWeapon(ThrowableWeapon&& other) noexcept = delete;
	ThrowableWeapon& operator=(ThrowableWeapon&& other) noexcept = delete;

	void Update(Entity* pOwner, float deltaTime) override;
	bool IsGrounded() const;
	bool AllowDelete() const;
	virtual void OnHit() = 0;

protected:
	ThrowableWeapon(int damage, const Point2f& from, const Point2f& to, float throwTime);

	bool Collision();
	void SetHitBox(float width, float height);

	bool m_IsGrounded{ false };
	bool m_AllowDelete{ false };
	RigidBody m_RigidBody{};
};