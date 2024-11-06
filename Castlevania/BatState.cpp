#include "pch.h"
#include "BatState.h"
#include "Bat.h"
#include "myUtils.h"

BatState::Idle::Idle(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "idle");
}

void BatState::Idle::Update(Entity* pEntity, float deltaTime)
{
}

EntityState* BatState::Idle::GetNextState(Entity* pEntity, float deltaTime)
{
	const float alertDistance{ 300 };

	if(GetPlayerDistance(pEntity).Length() < alertDistance)
		return new AlertState{ pEntity };

	return nullptr;
}

BatState::AlertState::AlertState(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "alert");
}

void BatState::AlertState::Update(Entity* pEntity, float deltaTime)
{
	m_Timer += deltaTime;
}

EntityState* BatState::AlertState::GetNextState(Entity* pEntity, float deltaTime)
{
	const float alertDistance{ 300 };
	const Vector2f playerDistance{ GetPlayerDistance(pEntity) };

	if(playerDistance.Length() > alertDistance)
		return new Idle{ pEntity };
	
	if(m_Timer > m_AttackTime)
		return new AttackState{ pEntity, playerDistance };
	
	return nullptr;
}

BatState::AttackState::AttackState(Entity* pEntity, const Vector2f& distance)
	: m_Origin{ pEntity->GetPivot() }
{
	SetActiveAnimation(pEntity, "attack");
	m_Direction = (distance.x > 0) ? 1 : -1;
	
	const bool isFlipped{ m_Direction == 1 };
	SetFlip(pEntity, isFlipped);

	GetSoundManager().PlaySound("BatAlert");
}

void BatState::AttackState::Update(Entity* pEntity, float deltaTime)
{
	const float amplitude{ 50 };
	const float priodLength{ 100 };
	const Vector2f moveSpeed{ 100, 100 };
	Point2f pivot{ pEntity->GetPivot() };

	pivot.x += moveSpeed.x * deltaTime * m_Direction;

	// change up or down depending on the distance to the player
	if(GetPlayerDistance(pEntity).y < 0)
		m_Intercept -= moveSpeed.y * deltaTime;
	else
		m_Intercept += moveSpeed.y * deltaTime;

	const float sineDistance{ abs(m_Origin.x - pivot.x) };
	pivot.y = m_Origin.y + m_Intercept + myUtils::CalcSineWave(sineDistance, amplitude, priodLength);

	SetRigidPivot(pEntity, pivot);
}

EntityState* BatState::AttackState::GetNextState(Entity* pEntity, float deltaTime)
{
	return nullptr;
}
