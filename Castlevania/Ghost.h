#pragma once
#include "Enemy.h"

class Ghost : public Enemy
{
public:
	Ghost(const Point2f& pivot, const EntityData& entityData);
	virtual ~Ghost() = default;

	Ghost(const Ghost& other) = delete;
	Ghost& operator=(const Ghost& other) = delete;
	Ghost(Ghost&& other) noexcept = delete;
	Ghost& operator=(Ghost&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;

	bool Hurt(const Rectf& hitBox, int damage) override;

private:
	void UpdateRigidBody(float deltaTime) override;
	void UpdateSprite(float deltaTime) override;

	Rectf m_TravelBounds{};
};