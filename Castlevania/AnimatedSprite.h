#pragma once
#include "Sprite.h"
#include "myStructs.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(const Texture* pTexture, const Point2f& bottomLeft = Point2f{}, float scale = 1.0f);
	AnimatedSprite(const Texture* pTexture, const Anim& animation, const Point2f& bottomLeft = Point2f{}, float scale = 1.0f);
	virtual ~AnimatedSprite() = default;

	AnimatedSprite(const AnimatedSprite& other) = delete;
	AnimatedSprite(AnimatedSprite&& other) noexcept = delete;
	AnimatedSprite& operator=(const AnimatedSprite& other) = delete;
	AnimatedSprite& operator=(AnimatedSprite&& other) noexcept = delete;

	void Update(float elapsedSec) override;

	float GetAnimationTime() const;
	bool IsLastFrame() const;
	bool IsReversed() const;

	void SetAnimation(const Anim& animation);
	void SetReverse(bool isReversing);
	void FullReverse();

protected:
	const Anim& GetAnim() const;
	virtual int GetCol() const;
	virtual int GetRow() const;

	float m_AccumTime{ 0.0f };
	bool m_Flipped{ false };

private:
	const Rectf GetSrcRect() const;

	Anim m_Anim{};
};