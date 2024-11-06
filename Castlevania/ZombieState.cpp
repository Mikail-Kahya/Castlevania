#include "pch.h"
#include "ZombieState.h"
#include "BloodSplatter.h"
#include "Entity.h"
#include "myUtils.h"

ZombieState::Wait::Wait()
{
	const float maxWaitTime{ 2 };
	m_SpawnTimer = myUtils::GenRand(maxWaitTime);
}

void ZombieState::Wait::Update(Entity* pEntity, float deltaTime)
{
	const Vector2f playerDistance{ GetPlayerDistance(pEntity) };
	const float alertDistance{ 200 };
	const float activeZone{ 50 };
	if (m_IsWaiting)
	{
		const bool inRange{ abs(playerDistance.x) < alertDistance && abs(playerDistance.y) < activeZone };
		m_IsWaiting = !inRange;
	}
	else
	{
		m_SpawnTimer -= deltaTime;
	}
}

EntityState* ZombieState::Wait::GetNextState(Entity* pEntity, float deltaTime)
{
	if (!m_IsWaiting && m_SpawnTimer < 0)
		return new Rise{ pEntity };

	return nullptr;
}

ZombieState::Rise::Rise(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "rise");
	FacePlayer(pEntity);
}

EntityState* ZombieState::Rise::GetNextState(Entity* pEntity, float deltaTime)
{
	if (IsLastFrame(pEntity))
		return new Walk{ pEntity };

	return nullptr;
}

ZombieState::Walk::Walk(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "walk");
	SetAllowHurt(pEntity, true);
}

void ZombieState::Walk::Update(Entity* pEntity, float deltaTime)
{
	float walkSpeed{ 20 };
	const float hurtPenalty{ 10 };

	if (IsHurt(pEntity))
		walkSpeed -= hurtPenalty;
	if (GetPlayerDistance(pEntity).x < 0)
		walkSpeed *= -1;

	FacePlayer(pEntity);
	SetVelocityX(pEntity, walkSpeed);
}

ZombieState::Die::Die(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "die");
	SetVelocityX(pEntity, 0);
}

void ZombieState::Die::Update(Entity* pEntity, float deltaTime)
{
	SprayBlood(pEntity, deltaTime);

	if (IsLastFrame(pEntity))
		SetDelete(pEntity, true);
}

void ZombieState::Die::SprayBlood(Entity* pEntity, float deltaTime)
{
	m_Timer += deltaTime;
	const float bloodSplatterDelay{ 0.2f };
	if (m_Timer < bloodSplatterDelay) return;

	m_Timer -= bloodSplatterDelay;
	const Point2f randomBottomLeft{ myUtils::GetRandPointInRect(pEntity->GetHurtBox()) };
	BloodSplatter* pBloodSplatter{ new BloodSplatter{ randomBottomLeft } };
	if (randomBottomLeft.x > pEntity->GetPivot().x)
		pBloodSplatter->Flip();
	GetParticleManager().AddParticle(pBloodSplatter);
}