#pragma once
#include "FloatingParticle.h"

class FadingParticle : public FloatingParticle
{
public:
	FadingParticle() = default;
	virtual ~FadingParticle() = default;

	FadingParticle(const FadingParticle& other) = delete;
	FadingParticle& operator=(const FadingParticle& other) = delete;
	FadingParticle(FadingParticle&& other) noexcept = delete;
	FadingParticle& operator=(FadingParticle&& other) noexcept = delete;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;
	Particle* GetNextParticle() const override { return nullptr; }
};
