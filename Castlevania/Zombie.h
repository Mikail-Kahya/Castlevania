#pragma once
#include "Enemy.h"

class Zombie : public Enemy
{
public:
	Zombie(const Point2f& pivot, const EntityData& entityData);
	virtual ~Zombie() = default;

	Zombie(const Zombie& other) = delete;
	Zombie& operator=(const Zombie& other) = delete;
	Zombie(Zombie&& other) noexcept = delete;
	Zombie& operator=(Zombie&& other) noexcept = delete;

	void Draw() const override;
	bool Hurt(const Rectf& hitBox, int damage) override;
};