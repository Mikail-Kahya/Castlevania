#pragma once
#include "FadingParticle.h"

class Explosion : public FadingParticle
{
public:
	Explosion(const Point2f& pivot);
	virtual ~Explosion() override;

	Explosion(const Explosion& other) = delete;
	Explosion& operator=(const Explosion& other) = delete;
	Explosion(Explosion&& other) noexcept = delete;
	Explosion& operator=(Explosion&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;

private:
	void Setup(const Point2f& pivot);

	AnimatedSprite* m_pSprite{ nullptr };
};