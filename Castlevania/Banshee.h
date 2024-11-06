#pragma once
#include "Enemy.h"
class Weapon;

class Banshee : public Enemy
{
public:
	Banshee(const Point2f& pivot, const EntityData& entityData);
	virtual ~Banshee() override;

	Banshee(const Banshee& other) = delete;
	Banshee& operator=(const Banshee& other) = delete;
	Banshee(Banshee&& other) noexcept = delete;
	Banshee& operator=(Banshee&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;
	bool Hurt(const Rectf& hitBox, int damage) override;

	void SetOpacity(float opacity);

private:
	bool IsAttacking() const;
	void UpdateRigidBody(float deltaTime) override;
	void UpdateSprite(float deltaTime) override;

	Weapon* m_pWeapon{ nullptr };
	float m_Opacity{ 0 };
};