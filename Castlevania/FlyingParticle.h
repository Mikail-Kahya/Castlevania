#pragma once
#include "FadingParticle.h"

class FlyingParticle : public FadingParticle
{
public:
	FlyingParticle(const Point2f& bottomLeft, const Vector2f& velocity);
	virtual ~FlyingParticle() = default;

	FlyingParticle(const FlyingParticle& other) = delete;
	FlyingParticle& operator=(const FlyingParticle& other) = delete;
	FlyingParticle(FlyingParticle&& other) noexcept = delete;
	FlyingParticle& operator=(FlyingParticle&& other) noexcept = delete;

	void Update(float deltaTime) override;
	virtual void Draw() const = 0;

protected:
	Point2f m_BottomLeft{};
	Vector2f m_Velocity{};
};