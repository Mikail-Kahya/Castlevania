#pragma once
#include "Weapon.h"

class SpecialAttack : public Weapon
{
public:
	SpecialAttack(Entity* pOwner);
	virtual ~SpecialAttack() = default;

	SpecialAttack(const SpecialAttack& other) = delete;
	SpecialAttack& operator=(const SpecialAttack& other) = delete;
	SpecialAttack(SpecialAttack&& other) noexcept = delete;
	SpecialAttack& operator=(SpecialAttack&& other) noexcept = delete;

	void Update(Entity* pOwner, float deltaTime) override;

private:
	void Reposition(Entity* pOwner);
	void SpawnParticles();
};