#pragma once
#include "BreakingParticle.h"

class Exploding : public BreakingParticle
{
public:
	Exploding(const Point2f& pivot, const Vector2f& velocity, BasicSprite* pSprite);
	virtual ~Exploding() override;

	Exploding(const Exploding& other) = delete;
	Exploding& operator=(const Exploding& other) = delete;
	Exploding(Exploding&& other) noexcept = delete;
	Exploding& operator=(Exploding&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;

private:
	void Setup(const Point2f& pivot, const Vector2f& velocity);

	Sprite* m_pSprite{ nullptr };
};