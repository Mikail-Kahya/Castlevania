#pragma once
#include "Weapon.h"

class ArthrovertaClaw : public Weapon
{
public:
	ArthrovertaClaw(const Point2f& pivot, int damage);
	virtual ~ArthrovertaClaw() override;

	ArthrovertaClaw(const ArthrovertaClaw& other) = delete;
	ArthrovertaClaw& operator=(const ArthrovertaClaw& other) = delete;
	ArthrovertaClaw(ArthrovertaClaw&& other) noexcept = delete;
	ArthrovertaClaw& operator=(ArthrovertaClaw&& other) noexcept = delete;

	void Draw() const override;
	void Update(Entity* pOwner, float deltaTime) override;
	bool Use(float delay) override;

private:
	enum class State { sendOut, swing, retract };

	void UpdateSprites(const Point2f& pivot, float deltaTime);
	void SendOutClaw();
	void SwingClaw();
	void RetractClaw();
	void Reset(float lerpTime);

	void SetupHitBox(const Point2f& pivot);

	void UpdateSwing(const Point2f& pivot);
	void UpdateHitBox(const Point2f& pivot, float deltaTime);

	void SetPivot(const Point2f& pivot);
	Point2f GetPivot() const;

	Sprite* m_pSprite{ nullptr };
	const Vector2f m_BaseShoulderOffset{ 20, 100 };
	Vector2f m_ShoulderOffset{};
	State m_AttackState{};
	float m_StartHeight{};
	float m_StateTimer{};
	float m_LerpTime{};
	Vector2f m_Start{};
};