#include "pch.h"
#include "Camera.h"
#include "myUtils.h"
#include <algorithm>

Camera::Camera(float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_LevelBoundaries{ Rectf{0.0f, 0.0f, width, height} }
	, m_Zoom{ Vector2f{1.0f, 1.0f} }
{
}

void Camera::Update(const Rectf& trackBox, float deltaTime)
{
	Update(Track(trackBox), deltaTime);
}

void Camera::Update(Point2f trackPoint, float deltaTime)
{
	const bool wasMoving{ m_IsMoving };

	const Vector2f velocity{ GetPlayer()->GetVelocity() };
	const float epsilon{ 0.05f };
	m_IsMoving = abs(velocity.x) > epsilon || abs(velocity.y) > epsilon;

	Clamp(trackPoint);

	if(m_IsEasing)
	{
		Ease(trackPoint, deltaTime);
	}
	else
	{
		m_EasePoint = trackPoint;
		m_IsEasing = wasMoving != m_IsMoving;
	}

	m_Tracker = trackPoint;
	
}

void Camera::View() const
{
	glScalef(m_Zoom.x, m_Zoom.y, 0.0f);
	glTranslatef(-m_Tracker.x, -m_Tracker.y, 0.0f);
}

void Camera::SetZoom(const Vector2f& zoom)
{
	m_Zoom = zoom;
}

void Camera::SetLevelBoundaries(const Rectf& boundary)
{
	m_LevelBoundaries = boundary;
}

void Camera::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}


Point2f Camera::Track(const Rectf& target) const
{
	const Point2f pivot{	target.left + target.width / 2, 
							target.bottom + target.height / 2 };

	return Point2f{ pivot.x - m_Width / 2, pivot.y - m_Height / 2 };
}

void Camera::Clamp(Point2f& trackPoint)
{
	// use standard min and max

	const float minX{ m_LevelBoundaries.left };
	const float maxX{ m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width };
	const float minY{ m_LevelBoundaries.bottom };
	const float maxY{ m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height};

	// check clamping bottom and left
	trackPoint.x = std::max(minX, trackPoint.x);
	trackPoint.y = std::max(minY, trackPoint.y);

	// check clamping top and right
	trackPoint.x = std::min(maxX, trackPoint.x);
	trackPoint.y = std::min(maxY, trackPoint.y);

}

void Camera::Ease(Point2f& trackPoint, float deltaTime)
{
	m_Ease.Activate(deltaTime);
	const float ratio{ m_Ease.GetRatio() };
	trackPoint = myUtils::Lerp(m_EasePoint, trackPoint, ratio);

	const float epsilon{ 0.005f };
	m_IsEasing = 1 - ratio >= epsilon;
	if (!m_IsEasing)
		m_Ease.Reset();

	Clamp(trackPoint);
}