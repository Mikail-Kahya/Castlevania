#pragma once
#include "FlyingParticle.h"

class DamageNumber : public FlyingParticle
{
public:
	DamageNumber(const Point2f& pivot, int damage, const Color4f& color = Color4f{ 1,1,1,1 });
	virtual ~DamageNumber() override;

	DamageNumber(const DamageNumber& other) = delete;
	DamageNumber& operator=(const DamageNumber& other) = delete;
	DamageNumber(DamageNumber&& other) noexcept = delete;
	DamageNumber& operator=(DamageNumber&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;

private:
	void DrawBackground() const;

	Sprite* m_pSprite{ nullptr };
	float m_Timer{};
};