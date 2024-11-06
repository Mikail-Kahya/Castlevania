#pragma once
#include "FadingParticle.h"

class Dust : public FadingParticle
{
public:
	Dust(const Point2f& pivot, float scale = 0);
	virtual ~Dust() override;

	Dust(const Dust& other) = delete;
	Dust& operator=(const Dust& other) = delete;
	Dust(Dust&& other) noexcept = delete;
	Dust& operator=(Dust&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;

private:
	void Setup(const Point2f& pivot, float scale);

	AnimatedSprite* m_pSprite{ nullptr };
};