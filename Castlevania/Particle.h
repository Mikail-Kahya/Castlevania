// Abstract Particle class
// Every particle derives from this class
// Particle holds a sprite but has can only draw from it, not delete it
// Levels:
	// 1 Particle: abstract
	// 2 Type of particle implementing basic behaviour (dynamic, floating) : abstract
	// 3 Derived class implementing complex behaviour (floating => fading, dynamic => exploding)
	// 4 Specific derived if none of these cover the specific behaviour
#pragma once

class Particle
{
public:
	Particle() = default;
	virtual ~Particle() = default;

	Particle(const Particle& other) = delete;
	Particle& operator=(const Particle& other) = delete;
	Particle(Particle&& other) noexcept = delete;
	Particle& operator=(Particle&& other) noexcept = delete;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;
	virtual Particle* GetNextParticle() const = 0;
	bool AllowDelete() const;

protected:
	bool m_Delete{ false };
};