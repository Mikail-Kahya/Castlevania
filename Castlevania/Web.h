#pragma once
#include "ThrowableWeapon.h"

class Web : public ThrowableWeapon
{
public:
	Web(const Point2f& from, const Point2f& to);
	virtual ~Web() override;

	Web(const Web& other) = delete;
	Web& operator=(const Web& other) = delete;
	Web(Web&& other) noexcept = delete;
	Web& operator=(Web&& other) noexcept = delete;

	void Draw() const override;
	void Update(Entity* pOwner, float deltaTime) override;
	void OnHit() override;

private:
	void ChangeAnimation();
	void FadeOut(float deltaTime);

	Avatar* m_pSprite{ nullptr };
	bool m_IsOpen{ false };
	bool m_IsFading{ false };
	float m_Opacity{ 1 };
};