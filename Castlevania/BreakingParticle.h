#pragma once
#include "DynamicParticle.h"

class BreakingParticle : public DynamicParticle
{
public:
	BreakingParticle() = default;
	virtual ~BreakingParticle() = default;

	BreakingParticle(const BreakingParticle& other) = delete;
	BreakingParticle& operator=(const BreakingParticle& other) = delete;
	BreakingParticle(BreakingParticle&& other) noexcept = delete;
	BreakingParticle& operator=(BreakingParticle&& other) noexcept = delete;

	virtual void Draw() const = 0;
	Particle* GetNextParticle() const override;

protected:
	void SetExplodeParticle(Particle* explodeParticle);

private:
	Particle* m_ExplodeParticle{};
};
