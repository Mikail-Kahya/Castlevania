#pragma once
#include "utils.h"

using vertexCollection = std::vector<std::vector<Point2f>>;
using vertexShape = std::vector<Point2f>;

class RigidBody final
{
public:

	RigidBody();
	RigidBody(const Point2f& pivot, float width, float height, const Vector2f& velocity = Vector2f{});
	~RigidBody() = default;

	RigidBody(const RigidBody& other) = default;
	RigidBody& operator=(const RigidBody& other) = default;
	RigidBody(RigidBody&& other) noexcept = default;
	RigidBody& operator=(RigidBody&& other) noexcept = default;

	void UpdatePhysics(float elapsedSec);
	bool CollideHard();
	void CollideSoft();
	void ResetCollision();

	Rectf GetHurtBox() const;
	const Point2f& GetPivot() const;
	Point2f GetCenter() const;
	const Vector2f& GetVelocity() const;
	bool IsGrounded() const;

	void SetPivot(const Point2f& pivot);
	void SetCenter(const Point2f& center);
	void SetVelocity(const Vector2f& velocity);
	void SetHeight(float height);
	void SetWidth(float width);

	static const Vector2f GRAVITY;

private:
	bool CheckCollision(const Point2f& rayP1, const Point2f& rayP2, const std::vector<std::vector<Point2f>>& vertices, utils::HitInfo& hitInfo);

	bool CollideHardVertical(const std::vector<std::vector<Point2f>>& vertices);
	bool CollideHardHorizontal(const std::vector<std::vector<Point2f>>& vertices);

	float m_Width{};
	float m_Height{};
	Point2f m_Pivot{};
	Vector2f m_Velocity{};
	bool m_OnHardCollision{};
	bool m_OnSoftCollision{};
};

