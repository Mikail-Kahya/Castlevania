#pragma once
#include "FloatingParticle.h"

class RepeatingParticle : public FloatingParticle
{
public:
	RepeatingParticle() = default;
	virtual ~RepeatingParticle() = default;

	RepeatingParticle(const RepeatingParticle& other) = delete;
	RepeatingParticle& operator=(const RepeatingParticle& other) = delete;
	RepeatingParticle(RepeatingParticle&& other) noexcept = delete;
	RepeatingParticle& operator=(RepeatingParticle&& other) noexcept = delete;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;
	Particle* GetNextParticle() const override;

protected:
	void SetRepeatingParticle(Particle* repeatingParticle);

	bool m_Repeat{ false };

private:
	Particle* m_RepeatingParticle{ nullptr };
};
