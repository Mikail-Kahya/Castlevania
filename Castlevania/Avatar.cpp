#include "pch.h"
#include "Avatar.h"

Avatar::Avatar(const Texture* pTexture, const Point2f& bottomLeft, float scale)
	: AnimatedSprite(pTexture, bottomLeft, scale)
{
}

void Avatar::SetAnimations(const std::map<std::string, Anim>& animMap)
{
	m_AnimMap = animMap;
}

void Avatar::AddAnimation(const std::string& id, const Anim& newAnimation)
{
	m_AnimMap.insert({ id, newAnimation });
}

void Avatar::SetActiveAnimation(const std::string& id)
{
	SetAnimation(m_AnimMap[id]);
	m_AccumTime = 0;
}