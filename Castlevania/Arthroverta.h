#pragma once
#include "Enemy.h"
#include "ArthrovertaState.h"
#include "Equipment.h"

class Arthroverta : public Enemy
{
public:
	Arthroverta(const Point2f& pivot, const EntityData& entityData);
	virtual ~Arthroverta() = default;

	Arthroverta(const Arthroverta& other) = delete;
	Arthroverta& operator=(const Arthroverta& other) = delete;
	Arthroverta(Arthroverta&& other) noexcept = delete;
	Arthroverta& operator=(Arthroverta&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;
	bool Hurt(const Rectf& hitBox, int damage) override;

	static bool m_BossDefeated;

private:
	friend class ArthrovertaState::Base;

	void SpawnParts() const;
	void UpdateRoll(float deltaTime);

	bool IsAttacking() const;
	bool IsRolling() const;

	Equipment m_Equipment{};
	float m_RollDustTimer{};
};