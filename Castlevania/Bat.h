#pragma once
#include "Enemy.h"

class Bat : public Enemy
{
public:
	Bat(const Point2f& pivot, const EntityData& entityData);
	virtual ~Bat() = default;

	Bat(const Bat& other) = delete;
	Bat& operator=(const Bat& other) = delete;
	Bat(Bat&& other) noexcept = delete;
	Bat& operator=(Bat&& other) noexcept = delete;

	bool Hurt(const Rectf& hitBox, int damage) override;

private:
	void UpdateRigidBody(float deltaTime) override {}
	void UpdateSprite(float deltaTime) override;
};