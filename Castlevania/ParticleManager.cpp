#include "pch.h"
#include "ParticleManager.h"
#include "Particle.h"

ParticleManager::~ParticleManager()
{
	ClearVector();
}

void ParticleManager::Draw() const
{
	for (Particle* pParticle : m_pParticleVec)
		pParticle->Draw();
}

void ParticleManager::Update(float deltaTime)
{
	if (Level::RoomChanged())
		ClearVector();

	for (int index{}; index < m_pParticleVec.size(); ++index)
	{
		Particle* pParticle{ m_pParticleVec[index] };

		pParticle->Update(deltaTime);
\
		if(pParticle->GetNextParticle())
		{
			ReplaceParticle(pParticle);
			m_pParticleVec[index] = pParticle;
		}

		if (pParticle->AllowDelete())
			DeleteParticle(index);
	}
}

void ParticleManager::AddParticle(Particle* pParticle)
{
	m_pParticleVec.push_back(pParticle);
}

void ParticleManager::ClearVector()
{
	for (Particle* pParticle : m_pParticleVec)
		delete pParticle;
	
	m_pParticleVec.clear();
}

void ParticleManager::DeleteParticle(int index)
{
	// switch element at index and last position
	const int lastIndex{ int(m_pParticleVec.size()) - 1 };
	Particle* pTemp{ m_pParticleVec[lastIndex] };
	m_pParticleVec[lastIndex] = m_pParticleVec[index];
	m_pParticleVec[index] = pTemp;

	// remove element from vector
	delete m_pParticleVec[lastIndex];
	m_pParticleVec.pop_back();
}

void ParticleManager::ReplaceParticle(Particle*& pParticle)
{
	Particle* pNextParticle{ pParticle->GetNextParticle()};
	if(pNextParticle)
	{
		delete pParticle;
		pParticle = pNextParticle;
	}
}