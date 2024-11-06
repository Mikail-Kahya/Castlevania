#pragma once
#include "FadingParticle.h"

class Sparkle : public FadingParticle
{
public:
	Sparkle(const Point2f& center, bool isBlue = false, float maxTime = 1.5f, int index = -1);
	virtual ~Sparkle() override;

	Sparkle(const Sparkle& other) = delete;
	Sparkle& operator=(const Sparkle& other) = delete;
	Sparkle(Sparkle&& other) noexcept = delete;
	Sparkle& operator=(Sparkle&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;

protected:
	void SetCenter(const Point2f& center);

private:
	void SetupSprite(const Point2f& center, bool isBlue, int index);
	float GetOpacity() const;

	BasicSprite* m_pSprite{};
	float m_ParticleTime{};
	float m_ParticleTimer{};
};