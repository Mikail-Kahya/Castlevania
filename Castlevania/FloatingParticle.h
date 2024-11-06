#pragma once
#include "Particle.h"
class Sprite;

class FloatingParticle : public Particle
{
public:
	FloatingParticle() = default;
	virtual ~FloatingParticle() = default;

	FloatingParticle(const FloatingParticle& other) = delete;
	FloatingParticle& operator=(const FloatingParticle& other) = delete;
	FloatingParticle(FloatingParticle&& other) noexcept = delete;
	FloatingParticle& operator=(FloatingParticle&& other) noexcept = delete;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;
	virtual Particle* GetNextParticle() const = 0;
};