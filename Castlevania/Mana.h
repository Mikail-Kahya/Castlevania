#pragma once
#include "PickUp.h"
class AnimatedSprite;
class Texture;

class Mana : public PickUp
{
public:
	explicit Mana(const Point2f& spawn);
	virtual ~Mana() = default;

	Mana(const Mana& other) = delete;
	Mana& operator=(const Mana& other) = delete;
	Mana(Mana&& other) noexcept = delete;
	Mana& operator=(Mana&& other) noexcept = delete;

	void Update(float deltaTime) override;
	bool Collect() override;

private:
	void Setup(const Point2f& spawn);

	void UpdateRigidBody(float deltaTime) override;
	void UpdateSprite(float deltaTime);
	void UpdateSine(float deltaTime);

	AnimatedSprite* m_pSprite{ nullptr };
	const int m_ManaIncrease{ 1 };
	const Point2f m_Origin{};
	const float m_Amplitude{ 15 };
	const float m_PeriodLength{ 30 };
	const float m_MoveSpeed{ 30 };
};
