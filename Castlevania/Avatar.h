#pragma once
#include "AnimatedSprite.h"
#include <map>

class Texture;

class Avatar : public AnimatedSprite
{
public:
	explicit Avatar(const Texture* pTexture, const Point2f& bottomLeft = Point2f{}, float scale = 1);
	virtual ~Avatar() = default;

	Avatar(const Avatar& other) = delete;
	Avatar(Avatar&& other) noexcept = delete;
	Avatar& operator=(const Avatar& other) = delete;
	Avatar& operator=(Avatar&& other) noexcept = delete;

	void SetAnimations(const std::map<std::string, Anim>& animMap);
	void AddAnimation(const std::string& id, const Anim& newAnimation);
	void SetActiveAnimation(const std::string& id);

private:
	std::map<std::string, Anim> m_AnimMap{};
};