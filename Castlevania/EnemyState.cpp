#include "pch.h"
#include "EnemyState.h"
#include "Enemy.h"

Vector2f EnemyState::GetPlayerDistance(Entity* pEntity) const
{
	return Vector2f{ pEntity->GetPivot(), GetPlayer()->GetPivot() };
}

void EnemyState::FacePlayer(Entity* pEntity)
{
	const Vector2f playerDistance{ GetPlayerDistance(pEntity) };
	SetFlip(pEntity, playerDistance.x > 0);
}

void EnemyState::SetDelete(Entity* pEntity, bool allowDelete)
{
	dynamic_cast<Enemy*>(pEntity)->m_AllowDelete = allowDelete;
}

void EnemyState::SetAllowHurt(Entity* pEntity, bool allowHurt)
{
	dynamic_cast<Enemy*>(pEntity)->m_AllowHurt = allowHurt;
}
