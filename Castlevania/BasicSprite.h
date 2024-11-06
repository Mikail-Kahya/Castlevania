#pragma once
#include "Sprite.h"

class BasicSprite : public Sprite
{
public:
	BasicSprite(const Texture* pTexture, const Point2f& bottomLeft = Point2f{}, float scale = 1);
	virtual ~BasicSprite() = default;

	BasicSprite(const BasicSprite& other) = delete;
	BasicSprite(BasicSprite&& other) noexcept = delete;
	BasicSprite& operator=(const BasicSprite& other) = delete;
	BasicSprite& operator=(BasicSprite&& other) noexcept = delete;

	void Update(float elapsedSec) override {}
	void SetSrcRect(const Rectf& srcRect);
};