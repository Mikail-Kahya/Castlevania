#pragma once
#include "FadingParticle.h"

class BloodSplatter : public FadingParticle
{
public:
	BloodSplatter(const Point2f& bottomLeft);
	virtual ~BloodSplatter() override;

	BloodSplatter(const BloodSplatter& other) = delete;
	BloodSplatter& operator=(const BloodSplatter& other) = delete;
	BloodSplatter(BloodSplatter&& other) noexcept = delete;
	BloodSplatter& operator=(BloodSplatter&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;

	void Flip() const;

private:

	AnimatedSprite* m_pSprite{ nullptr };
};