#pragma once
#include <Vector2f.h>

class Camera final
{
public:
	Camera(float width, float height);
	~Camera() = default;

	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;
	Camera(Camera&& other) noexcept = delete;
	Camera& operator=(Camera&& other) noexcept = delete;

	void Update(const Rectf& trackBox, float deltaTime);
	void Update(Point2f trackPoint, float deltaTime);
	void View() const;

	void SetZoom(const Vector2f& zoom);
	void SetLevelBoundaries(const Rectf& boundary);
	void SetDimensions(float width, float height);

private:
	Point2f Track(const Rectf& target) const;
	void Clamp(Point2f& trackPoint);
	void Ease(Point2f& trackPoint, float deltaTime);

	float m_Width{};
	float m_Height{};
	Rectf m_LevelBoundaries{};
	Vector2f m_Zoom{};

	Point2f m_Tracker{};
	Point2f m_EasePoint{};

	bool m_IsEasing{ false };
	bool m_IsMoving{};
	EasingData m_Ease{ 0.7f };
};

