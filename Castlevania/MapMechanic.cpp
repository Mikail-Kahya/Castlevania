#include "pch.h"
#include "MapMechanic.h"
#include "PlayerState.h"

bool MapMechanic::IsPlayerCollidingHard() const
{
	return GetPlayer()->m_IsCollidingHard;
}

void MapMechanic::SetPlayerAvoidPlatforms(bool avoidPlatforms)
{
	GetPlayer()->m_AvoidPlatforms = avoidPlatforms;
}

void MapMechanic::SetPlayerState(PlayerState* pState)
{
	GetPlayer()->SetState(pState);
}

void MapMechanic::SetPlayerVelocity(const Vector2f& velocity)
{
	GetPlayer()->m_RigidBody.SetVelocity(velocity);
}

void MapMechanic::SetPlayerPivot(const Point2f& pivot)
{
	GetPlayer()->m_RigidBody.SetPivot(pivot);
}
