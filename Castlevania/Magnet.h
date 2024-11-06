#pragma once
#include "MapMechanic.h"
#include "myStructs.h"
class Sprite;

// Player holds shift and gets magnetized to the magnet
// Moving the mouse creates the tension of the magnet
// Releasing shift launches the player
// Player is in constant fall state

class Magnet : public MapMechanic
{
public:
	Magnet(const Point2f& bottomLeft);
	virtual ~Magnet() override;

	Magnet(const Magnet& other) = delete;
	Magnet& operator=(const Magnet& other) = delete;
	Magnet(Magnet&& other) noexcept = delete;
	Magnet& operator=(Magnet&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;

private:
	void Setup(const Point2f& bottomLeft);
	void ActivateMagnet();
	void PulseActiveEffect(float deltaTime);
	void Attract(float deltaTime);
	void Repel();
	void UpdateAttractionPoint();
	void LockPlayerControls(float deltaTime);

	Point2f GetPlayerCenter() const;
	float GetAttractRadius() const;

	Point2f m_Center{};
	Sprite* m_pMagnetSprite{};
	Sprite* m_pActiveSprite{};

	float m_ActiveOpacity{ 0.5f };
	float m_OpacityTimer{};
	bool m_OpacityRise{ true };

	bool m_IsActive{ false };
	bool m_IsRepelling{ false };
	bool m_IsRepelled{ false };
	float m_AttractTimer{};

	Vector2f m_LaunchVelocity{};
	Point2f m_AttractionPoint{};
};