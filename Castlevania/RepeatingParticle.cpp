#include "pch.h"
#include "RepeatingParticle.h"

Particle* RepeatingParticle::GetNextParticle() const
{
	if (m_Repeat)
		return m_RepeatingParticle;

	return nullptr;
}

void RepeatingParticle::SetRepeatingParticle(Particle* repeatingParticle)
{
	m_RepeatingParticle = repeatingParticle;
}
