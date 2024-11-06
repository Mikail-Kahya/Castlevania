#pragma once
#include "Particle.h"
#include "RigidBody.h"

class DynamicParticle : public Particle
{
public:
	DynamicParticle() = default;
	virtual ~DynamicParticle() = default;

	DynamicParticle(const DynamicParticle& other) = delete;
	DynamicParticle& operator=(const DynamicParticle& other) = delete;
	DynamicParticle(DynamicParticle&& other) noexcept = delete;
	DynamicParticle& operator=(DynamicParticle&& other) noexcept = delete;

	void Update(float deltaTime) override;
	virtual void Draw() const = 0;
	virtual Particle* GetNextParticle() const = 0;

protected:
	virtual void CheckCollision();
	RigidBody m_RigidBody{};
};