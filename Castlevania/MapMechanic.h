#pragma once

class MapMechanic
{
public:
	MapMechanic() = default;
	virtual ~MapMechanic() = default;

	MapMechanic(const MapMechanic& other) = delete;
	MapMechanic& operator=(const MapMechanic& other) = delete;
	MapMechanic(MapMechanic&& other) noexcept = delete;
	MapMechanic& operator=(MapMechanic&& other) noexcept = delete;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;

protected:
	bool IsPlayerCollidingHard() const;
	void SetPlayerAvoidPlatforms(bool avoidPlatforms);
	void SetPlayerState(PlayerState* pState);
	void SetPlayerVelocity(const Vector2f& velocity);
	void SetPlayerPivot(const Point2f& pivot);
};