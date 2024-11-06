#include "pch.h"
#include "FlyingParticle.h"

FlyingParticle::FlyingParticle(const Point2f& bottomLeft, const Vector2f& velocity)
	: m_BottomLeft{ bottomLeft }
	, m_Velocity{ velocity }
{
}

void FlyingParticle::Update(float deltaTime)
{
	m_BottomLeft += m_Velocity * deltaTime;
}
