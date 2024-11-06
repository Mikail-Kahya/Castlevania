#include "pch.h"
#include "RisingSparkle.h"
#include "myUtils.h"

RisingSparkle::RisingSparkle(const Point2f& center, bool isBlue, float maxTime, int index)
	: Sparkle(center, isBlue, maxTime, index)
	, m_Center{ center }
{
	const float maxY{ 50 };
	const float maxX{ 20 };
	m_Velocity = Vector2f{ myUtils::GenRand(-maxX, maxX), myUtils::GenRand(maxY) };
}

void RisingSparkle::Update(float deltaTime)
{
	Sparkle::Update(deltaTime);
	m_Center += m_Velocity * deltaTime;
	SetCenter(m_Center);
}