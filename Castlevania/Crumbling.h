#pragma once
#include "Exploding.h"

class Crumbling : public BreakingParticle
{
public:
	Crumbling(const Point2f& pivot, const Vector2f& velocity, BasicSprite* pSprite);
	virtual ~Crumbling() override;

	Crumbling(const Crumbling& other) = delete;
	Crumbling& operator=(const Crumbling& other) = delete;
	Crumbling(Crumbling&& other) noexcept = delete;
	Crumbling& operator=(Crumbling&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;

private:
	void Setup(const Point2f& pivot, const Vector2f& velocity);

	BasicSprite* m_pSprite{ nullptr };
};

