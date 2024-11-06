#include "pch.h"
#include "InAttackState.h"
#include "InCrouchState.h"
#include "InAirState.h"
#include "Player.h"
#include "myUtils.h"

InAttackState::InAttackState(Entity* pEntity, const std::string& state)
{
	const int right{ 4 };
	std::string hand{ "left" };
	if (m_MouseStates == right)
		hand = "right";

	DepleteStamina(pEntity, m_StaminaCost);
	SetVelocityX(pEntity, 0);
	SetActiveAnimation(pEntity, hand + state);
}

void InAttackState::Update(Entity* pEntity, float deltaTime)
{
	if (IsLastFrame(pEntity))
		StopAttack(pEntity);
}

void InAttackState::PlayAttackVoice()
{
	PlayVoiceSound("ShanoaAttack");
}

void InAttackState::PlayAttack()
{
	const int right{ 4 };
	int attackSoundIndex{ 0 };

	if (m_MouseStates == right)
		attackSoundIndex = 1;

	GetSoundManager().PlaySound("ShanoaAttack", attackSoundIndex);
}

void InAttackState::StopAttack(Entity* pEntity)
{
	m_Attacking = false;
	m_Finished = true;
	DisableActiveHand(pEntity);
}

CrouchAttackState::CrouchAttackState(Entity* pEntity)
	: InAttackState(pEntity, "Crouch")
{
	const float endHeight{ m_DefaultHurtBox.height / 1.8f };
	SetHurtHeight(pEntity, endHeight);

	PlayAttack();
	PlayAttackVoice();
}

void CrouchAttackState::Update(Entity* pEntity, float deltaTime)
{
	InAttackState::Update(pEntity, deltaTime);
}

EntityState* CrouchAttackState::GetNextState(Entity* pEntity, float deltaTime)
{
	const float slideDelay{ 0.5f };

	if(m_Finished)
		return new CrouchedState{ pEntity, slideDelay};
	
	return nullptr;
}

AttackState::AttackState(Entity* pEntity)
	: InAttackState(pEntity, "")
{
	PlayAttack();
	PlayAttackVoice();
}

EntityState* AttackState::GetNextState(Entity* pEntity, float deltaTime)
{
	if (m_Finished)
		return new IdleState{ pEntity };

	return nullptr;
}

AirAttackState::AirAttackState(Entity* pEntity)
	: InAttackState(pEntity, "Air")
{
	PlayAttack();
	PlayAttackVoice();
}

void AirAttackState::Update(Entity* pEntity, float deltaTime)
{
	HandleMovement(pEntity);

	if (IsLastFrame(pEntity) || IsGrounded(pEntity))
		StopAttack(pEntity);
}

EntityState* AirAttackState::GetNextState(Entity* pEntity, float deltaTime)
{
	if(IsGrounded(pEntity))
		return new IdleState{ pEntity };

	if (m_Finished)
		return new FallingState{ pEntity };
	
	return nullptr;
}

SpecialState::SpecialState(Entity* pEntity)
	: InAttackState(pEntity, "")
{
	GetSoundManager().StopEffects();
	GetSoundManager().PlaySound("ShanoaSpecial");
}

EntityState* SpecialState::GetNextState(Entity* pEntity, float deltaTime)
{
	if (m_Finished)
		return new IdleState{ pEntity };

	return nullptr;
}
