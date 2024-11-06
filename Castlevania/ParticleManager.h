#pragma once
#include "Level.h"
class Particle;
// Particle manager is a singleton.
// Use of singleton circumvents repeated transfer of particle objects
// throughout the program.
// Anything can make a particle when interacting.

class ParticleManager final
{
public:
	~ParticleManager();

	friend ParticleManager& GetParticleManager();

	ParticleManager(const ParticleManager& other) = delete;
	ParticleManager& operator=(const ParticleManager& other) = delete;
	ParticleManager(ParticleManager&& other) noexcept = delete;
	ParticleManager& operator=(ParticleManager&& other) noexcept = delete;

	void Draw() const;
	void Update(float deltaTime);

	void AddParticle(Particle* pParticle);

private:
	ParticleManager() = default;

	void ClearVector();
	void DeleteParticle(int index);
	void ReplaceParticle(Particle*& pParticle);

	std::vector<Particle*> m_pParticleVec{};
};

inline ParticleManager& GetParticleManager()
{
	static ParticleManager particleManager{};
	return particleManager;
}