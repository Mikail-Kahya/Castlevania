#pragma once
#include "Sparkle.h"

class RisingSparkle : public Sparkle
{
public:
	RisingSparkle(const Point2f& center, bool isBlue = false, float maxTime = 1.5f, int index = -1);
	virtual ~RisingSparkle() = default;

	RisingSparkle(const RisingSparkle& other) = delete;
	RisingSparkle& operator=(const RisingSparkle& other) = delete;
	RisingSparkle(RisingSparkle&& other) noexcept = delete;
	RisingSparkle& operator=(RisingSparkle&& other) noexcept = delete;

	void Update(float deltaTime) override;

private:
	Point2f m_Center{};
	Vector2f m_Velocity{};
};