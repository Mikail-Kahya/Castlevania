#include "pch.h"
#include "BansheeState.h"
#include "Banshee.h"

BansheeState::Idle::Idle(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "appear");
	SetAllowHurt(pEntity, false);
}

void BansheeState::Idle::Update(Entity* pEntity, float deltaTime)
{
	if(m_InRange)
	{
		const float opacityRate{ 1.5f };
		m_Opacity += opacityRate * deltaTime;
		dynamic_cast<Banshee*>(pEntity)->SetOpacity(m_Opacity);

		if (!m_UsedSound && m_Opacity > 0.5f)
		{
			m_UsedSound = true;
			GetSoundManager().PlaySound("BansheeSpawn");
		}
			
	}
	else
	{
		const float alertDistance{ 300 };
		m_InRange = GetPlayerDistance(pEntity).Length() < alertDistance;
	}
}

EntityState* BansheeState::Idle::GetNextState(Entity* pEntity, float deltaTime)
{
	if (m_Opacity > 1)
		return new Alert{ pEntity };

	return nullptr;
}

BansheeState::Alert::Alert(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "wakeUp");
	GetSoundManager().PlaySound("BansheeAlert");
}

EntityState* BansheeState::Alert::GetNextState(Entity* pEntity, float deltaTime)
{
	if (IsLastFrame(pEntity))
		return new Move{ pEntity };
	
	return nullptr;
}

BansheeState::Move::Move(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "move");
	SetAllowHurt(pEntity, true);
}

void BansheeState::Move::Update(Entity* pEntity, float deltaTime)
{
	const float moveSpeed{ 70 };
	const Vector2f direction{ GetPlayerDistance(pEntity).Normalized() };

	FacePlayer(pEntity);
	SetVelocity(pEntity, direction * moveSpeed);
}

EntityState* BansheeState::Move::GetNextState(Entity* pEntity, float deltaTime)
{
	const float attackRange{ 50 };
	if (GetPlayerDistance(pEntity).Length() < attackRange)
		return new AttackStart{ pEntity };

	return nullptr;
}

BansheeState::AttackStart::AttackStart(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "attackStart");
	SetVelocity(pEntity, Vector2f{});
}

EntityState* BansheeState::AttackStart::GetNextState(Entity* pEntity, float deltaTime)
{
	if (IsLastFrame(pEntity))
		return new Attack{ pEntity };

	return nullptr;
}

BansheeState::AttackEnd::AttackEnd(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "attackEnd");
}

EntityState* BansheeState::AttackEnd::GetNextState(Entity* pEntity, float deltaTime)
{
	if (IsLastFrame(pEntity))
		return new Move{ pEntity };

	return nullptr;
}

BansheeState::Attack::Attack(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "attack");
	GetSoundManager().PlaySound("BansheeAttack");
}

void BansheeState::Attack::Update(Entity* pEntity, float deltaTime)
{
	m_Timer += deltaTime;
}

EntityState* BansheeState::Attack::GetNextState(Entity* pEntity, float deltaTime)
{
	const float attackTime{ 2 };

	if (m_Timer > attackTime)
		return new AttackEnd{ pEntity };

	return nullptr;
}

BansheeState::Die::Die(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "attack");
	GetSoundManager().PlaySound("BansheeAlert");
}

void BansheeState::Die::Update(Entity* pEntity, float deltaTime)
{
	const float opacityRate{ 5 };
	m_Opacity -= opacityRate * deltaTime;
	dynamic_cast<Banshee*>(pEntity)->SetOpacity(m_Opacity);

	if (m_Opacity < 0)
		SetDelete(pEntity, true);
}