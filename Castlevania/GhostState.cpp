#include "pch.h"
#include "GhostState.h"
#include "Ghost.h"
#include "myUtils.h"

GhostState::Idle::Idle(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "idle");
}

void GhostState::Idle::Update(Entity* pEntity, float deltaTime)
{
	UpdatePosition(pEntity, deltaTime);
	UpdateAlert(pEntity, deltaTime);
}

EntityState* GhostState::Idle::GetNextState(Entity* pEntity, float deltaTime)
{
	if (m_Alert)
		return new Alert{ pEntity };

	return nullptr;
}

void GhostState::Idle::UpdatePosition(Entity* pEntity, float deltaTime)
{
	m_MoveTimer -= deltaTime;

	const float maxTime{ 2.5f };
	const float moveSpeed{ 10 };
	if (m_MoveTimer < 0)
	{
		m_MoveTimer = myUtils::GenRand(maxTime);

		const Vector2f velocity{ moveSpeed * myUtils::GetRandDirection(),
								moveSpeed * myUtils::GetRandDirection() };

		SetVelocity(pEntity, velocity);
		SetFlip(pEntity, velocity.x > 0);
	}
}

void GhostState::Idle::UpdateAlert(Entity* pEntity, float deltaTime)
{
	const float alertDistance{ 300 };
	const float alertTime{ 2 };
	if (GetPlayerDistance(pEntity).Length() < alertDistance)
	{
		m_AlertTimer += deltaTime;
		m_Alert = m_AlertTimer > alertTime;
	}
	else
	{
		m_AlertTimer = 0;
	}
}

GhostState::Alert::Alert(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "alert");
	SetVelocity(pEntity, Vector2f{});
}

void GhostState::Alert::Update(Entity* pEntity, float deltaTime)
{
	m_Timer += deltaTime;

	if (IsLastFrame(pEntity) && !m_IsPreparing)
		SetActiveAnimation(pEntity, "prepare");

	FacePlayer(pEntity);
}

EntityState* GhostState::Alert::GetNextState(Entity* pEntity, float deltaTime)
{
	const float alertTime{ 2 };
	if(alertTime < m_Timer)
		return new Attack{ pEntity };
	
	return nullptr;
}

GhostState::Attack::Attack(Entity* pEntity)
	: m_MoveFrom{ pEntity->GetPivot() }
	, m_MoveTo{ pEntity->GetPivot() + GetPlayerDistance(pEntity) }
{
	SetActiveAnimation(pEntity, "attack");
	FacePlayer(pEntity);
	GetSoundManager().PlaySound("GhostAttack");
}

void GhostState::Attack::Update(Entity* pEntity, float deltaTime)
{
	m_Timer += deltaTime;

	const Point2f pivot{ (1 - m_Timer) * m_MoveFrom.x + m_Timer * m_MoveTo.x,
						 (1 - m_Timer) * m_MoveFrom.y + m_Timer * m_MoveTo.y };
	SetRigidPivot(pEntity, pivot);
}

EntityState* GhostState::Attack::GetNextState(Entity* pEntity, float deltaTime)
{
	if (pEntity->GetPivot() == m_MoveTo)
		return new Idle{ pEntity };

	return nullptr;
}

GhostState::Die::Die(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "die");
	GetSoundManager().PlaySound("GhostDeath");
}

void GhostState::Die::Update(Entity* pEntity, float deltaTime)
{
	const float fallVelocity{ 260 };
	if (IsLastFrame(pEntity))
		SetVelocity(pEntity, Vector2f{ 0, -fallVelocity });
}