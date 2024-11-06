#include "pch.h"
#include "BreakingParticle.h"

Particle* BreakingParticle::GetNextParticle() const
{
	if (m_RigidBody.IsGrounded())
		return m_ExplodeParticle;

	return nullptr;
}

void BreakingParticle::SetExplodeParticle(Particle* explodeParticle)
{
	m_ExplodeParticle = explodeParticle;
}
