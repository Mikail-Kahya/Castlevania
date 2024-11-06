#include "pch.h"
#include "SkeletonRangedState.h"
#include "SkeletonRanged.h"
#include "Bone.h"
#include "myUtils.h"

#pragma region Base
void SkeletonRangedState::Base::ThrowBone(Entity* pEntity)
{
	const Point2f pivot{ pEntity->GetPivot() };
	Bone* pBone{ new Bone{ pivot, pivot + GetPlayerDistance(pEntity), GetDamage(pEntity) } };
	dynamic_cast<SkeletonRanged*>(pEntity)->m_pBone = pBone;
	GetSoundManager().PlaySound("ShanoaAttack");
}

bool SkeletonRangedState::Base::IsAttackReady(Entity* pEntity) const
{
	return !dynamic_cast<SkeletonRanged*>(pEntity)->m_pBone;
}

int SkeletonRangedState::Base::GetDamage(Entity* pEntity) const
{
	return dynamic_cast<SkeletonRanged*>(pEntity)->m_Stats.damage;
}
#pragma endregion Base

#pragma region Walk
SkeletonRangedState::Walk::Walk(Entity* pEntity)
	: m_Distance{ myUtils::GenRand(m_MinDistance, m_MaxDistance) }
{
	SetActiveAnimation(pEntity, "walk");
	m_Direction = myUtils::GetRandDirection();
}

void SkeletonRangedState::Walk::Update(Entity* pEntity, float deltaTime)
{
	const float moveSpeed{ 50 };
	SetVelocityX(pEntity, moveSpeed * m_Direction);
	FacePlayer(pEntity);
	m_Distance -= moveSpeed * deltaTime;
	if(m_Distance < 0)
	{
		m_Distance = myUtils::GenRand(m_MinDistance, m_MaxDistance);
		m_Direction = myUtils::GetRandDirection();
	}
}

EntityState* SkeletonRangedState::Walk::GetNextState(Entity* pEntity, float deltaTime)
{
	const Vector2f playerDistance{ GetPlayerDistance(pEntity) };

	const float jumpAlertDistance{ 50 };
	if (playerDistance.Length() < jumpAlertDistance)
		return new Jump{ pEntity };

	const float attackAlertDistance{ 150 };
	if (playerDistance.Length() < attackAlertDistance && IsAttackReady(pEntity))
		return new Attack{ pEntity };

	return nullptr;
}
#pragma endregion Walk

#pragma region Jump
SkeletonRangedState::Jump::Jump(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "jump");
	Vector2f jumpVelocity{ 100, 400 };
	// jump away from player
	jumpVelocity.x *= -GetDirection(pEntity);
	SetVelocity(pEntity, jumpVelocity);
}

EntityState* SkeletonRangedState::Jump::GetNextState(Entity* pEntity, float deltaTime)
{
	if (IsGrounded(pEntity))
		return new Land{ pEntity };

	return nullptr;
}
#pragma endregion Jump

#pragma region Land
SkeletonRangedState::Land::Land(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "land");
	SetVelocityX(pEntity, 0);
}

EntityState* SkeletonRangedState::Land::GetNextState(Entity* pEntity, float deltaTime)
{
	if (IsLastFrame(pEntity))
		return new Walk{ pEntity };

	return nullptr;
}
#pragma endregion Land

#pragma region Attack
SkeletonRangedState::Attack::Attack(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "attack");
}

void SkeletonRangedState::Attack::Update(Entity* pEntity, float deltaTime)
{
	if (m_Timer > m_ThrowDelay && IsAttackReady(pEntity))
		ThrowBone(pEntity);
	else
		m_Timer += deltaTime;
}

EntityState* SkeletonRangedState::Attack::GetNextState(Entity* pEntity, float deltaTime)
{
	if (IsLastFrame(pEntity))
		return new Walk{ pEntity };

	return nullptr;
}
#pragma endregion Attack

#pragma region Hurt
SkeletonRangedState::Hurt::Hurt(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "hurt");
	Vector2f bounceVelocity{ 50,200 };
	bounceVelocity.x *= GetDirection(pEntity);
	SetVelocity(pEntity, bounceVelocity);
}

EntityState* SkeletonRangedState::Hurt::GetNextState(Entity* pEntity, float deltaTime)
{
	if (IsLastFrame(pEntity))
		return new Walk{ pEntity };

	return nullptr;
}
#pragma endregion Hurt