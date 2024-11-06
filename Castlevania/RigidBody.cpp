#include "pch.h"
#include "RigidBody.h"
#include "Level.h"

const Vector2f RigidBody::GRAVITY{ Vector2f{0.0f, -981.0f } };

RigidBody::RigidBody()
	: RigidBody(Point2f{ 0.0f, 0.0f }, 0.0f, 0.0f, Vector2f{ 0.0f, 0.0f })
{
}

RigidBody::RigidBody(const Point2f& pivot, float width, float height, const Vector2f& velocity)
	: m_Width{ width }
	, m_Height{ height }
	, m_Pivot{ pivot }
	, m_Velocity{ velocity }
{
}

void RigidBody::UpdatePhysics(float elapsedSec)
{
	m_Velocity += GRAVITY * elapsedSec;
	m_Pivot += m_Velocity * elapsedSec;
}


bool RigidBody::CheckCollision(const Point2f& rayP1, const Point2f& rayP2, const vertexCollection& vertices, utils::HitInfo& hitInfo)
{	
	for (const vertexShape& vertVec : vertices)
	{
		if (utils::Raycast(vertVec, rayP1, rayP2, hitInfo))
			return true;
	}
	
	hitInfo = utils::HitInfo{};
	return false;
}

bool RigidBody::CollideHard()
{
	const bool collideVertical{ CollideHardVertical(Level::GetCollisions()) };
	const bool collideHorizontal{ CollideHardHorizontal(Level::GetCollisions()) };
	return collideVertical || collideHorizontal;
}

bool RigidBody::CollideHardVertical(const vertexCollection& vertices)
{
	m_OnHardCollision = false;
	utils::HitInfo hitInfo{};

	// check collision Y
	const float left{ m_Pivot.x - m_Width / 2 + m_Width / 5 };
	const float right{ m_Pivot.x + m_Width / 2 - m_Width / 5 };
	const float top{ m_Pivot.y + m_Height + 1 };
	const float bottom{ m_Pivot.y - 1 };

	const Point2f rayP1{ left, top };
	const Point2f rayP2{ left, bottom };
	bool collided{ CheckCollision(rayP1, rayP2, vertices, hitInfo) };

	if (!collided)
	{
		const Point2f rayP3{ right, top };
		const Point2f rayP4{ right, bottom };
		collided = CheckCollision(rayP3, rayP4, vertices, hitInfo);
	}

	if (collided)
	{
		const float threshold{ 0.5f };

		if (hitInfo.lambda > threshold && m_Velocity.y <= 0) // collide bottom
		{
			m_Pivot.y = hitInfo.intersectPoint.y + 1;
			m_OnHardCollision = true;
			m_Velocity.y = 0;
		}
		else if(hitInfo.lambda < threshold && m_Velocity.y >= 0) // collide top
		{
			m_Pivot.y = hitInfo.intersectPoint.y - m_Height - 2;
			m_Velocity.y = -50;
		}
		return true;
	}
	return false;
}

bool RigidBody::CollideHardHorizontal(const vertexCollection& vertices)
{
	utils::HitInfo hitInfo{};
	const float gap{ m_Height / 10 };

	const float right{ m_Pivot.x + m_Width / 2 + 1 };
	const float left{ m_Pivot.x - m_Width / 2 - 1 };
	const float bottom{ m_Pivot.y + m_Height - m_Height / 5 };
	const float top{ m_Pivot.y + m_Height / 5 };

	// check collision X at bottom
	const Point2f rayP1{ right, bottom };
	const Point2f rayP2{ left, bottom };
	bool collided{ CheckCollision(rayP1, rayP2, vertices, hitInfo) };

	// check collision X at top if not collided with the bottom ray
	if (!collided)
	{
		const Point2f rayP3{ right, top };
		const Point2f rayP4{ left, top };
		collided = CheckCollision(rayP3, rayP4, vertices, hitInfo);
	}


	if (collided)
	{
		const float threshold{ 0.5f };

		if (hitInfo.lambda > threshold && m_Velocity.x < 0) // collision left
		{
			m_Pivot.x = hitInfo.intersectPoint.x + m_Width / 2 + 1;
		}
		else if (hitInfo.lambda < threshold && m_Velocity.x > 0) // collision right
		{
			m_Pivot.x = hitInfo.intersectPoint.x - m_Width / 2 - 1;
		}
		m_Velocity.x = 0;
		return true;
	}
	return false;
}

void RigidBody::CollideSoft()
{
	m_OnSoftCollision = false;
	utils::HitInfo hitInfo{};

	// check collision Y
	const float left{ m_Pivot.x - m_Width / 2 + m_Width / 5 };
	const float right{ m_Pivot.x + m_Width / 2 - m_Width / 5 };
	const float top{ m_Pivot.y + m_Height + 1 };
	const float bottom{ m_Pivot.y - 1 };

	const Point2f rayP1{ left, top };
	const Point2f rayP2{ left, bottom };
	bool collided{ CheckCollision(rayP1, rayP2, Level::GetPlatforms(), hitInfo) };

	if (!collided)
	{
		const Point2f rayP3{ right, top };
		const Point2f rayP4{ right, bottom };
		collided = CheckCollision(rayP3, rayP4, Level::GetPlatforms(), hitInfo);
	}

	if (collided)
	{
		const float threshold{ 0.8f };

		if (hitInfo.lambda > threshold && m_Velocity.y <= 0) // collide bottom
		{
			m_Pivot.y = hitInfo.intersectPoint.y + 1;
			m_Velocity.y = 0;
			m_OnSoftCollision = true;
		}
	}
}

void RigidBody::ResetCollision()
{
	m_OnHardCollision = false;
	m_OnSoftCollision = false;
}


Rectf RigidBody::GetHurtBox() const
{
	const float x{ m_Pivot.x - m_Width / 2 };
	const float y{ m_Pivot.y };

	return Rectf{ x, y, m_Width, m_Height };
}

const Point2f& RigidBody::GetPivot() const
{
	return m_Pivot;
}

Point2f RigidBody::GetCenter() const
{
	return Point2f{ m_Pivot.x, m_Pivot.y + m_Height / 2 };
}

const Vector2f& RigidBody::GetVelocity() const
{
	return m_Velocity;
}

bool RigidBody::IsGrounded() const
{
	return m_OnHardCollision || m_OnSoftCollision;
}

void RigidBody::SetPivot(const Point2f& pivot)
{
	m_Pivot = pivot;
}

void RigidBody::SetCenter(const Point2f& center)
{
	m_Pivot.x = center.x;
	m_Pivot.y = center.y - m_Height / 2;
}

void RigidBody::SetVelocity(const Vector2f& velocity)
{
	m_Velocity = velocity;
}

void RigidBody::SetHeight(float height)
{
	m_Height = height;
}

void RigidBody::SetWidth(float width)
{
	m_Width = width;
}