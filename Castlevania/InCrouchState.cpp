#include "pch.h"
#include "InCrouchState.h"
#include "InAttackState.h"
#include "Entity.h"
#include "InAirState.h"

void InCrouchState::Update(Entity* pEntity, float deltaTime)
{
	ReplenishStamina(pEntity, deltaTime);
	HandleMouse(pEntity);
	SetVelocityX(pEntity, 0);

	if (KEY_STATES[SDL_SCANCODE_A])
		SetFlip(pEntity, true);
	else if (KEY_STATES[SDL_SCANCODE_D])
		SetFlip(pEntity, false);
}

EntityState* InCrouchState::GetNextState(Entity* pEntity, float deltaTime)
{
	const float epsilon{ 0.005f };

	if (m_Attacking)
		return new CrouchAttackState{ pEntity };

	if (IsFalling(pEntity))
		return new FallingState{ pEntity };

	if (KEY_STATES[SDL_SCANCODE_LSHIFT] && m_DodgeDelay < epsilon)
		return new Dodge{ pEntity };

	return nullptr;
}

CrouchState::CrouchState(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "crouch");
}

void CrouchState::Update(Entity* pEntity, float deltaTime)
{
	InCrouchState::Update(pEntity, deltaTime);
	const float height{ pEntity->GetHurtBox().height };
	const float endHeight{ m_DefaultHurtBox.height / 1.8f };

	const float stepTime{ GetAnimationTime(pEntity) / deltaTime };
	const float heightStep{ (m_DefaultHurtBox.height - endHeight) / stepTime };
	SetHurtHeight(pEntity, height - (heightStep));

	m_Timer += deltaTime;
	if (!m_IsSoundPlayed && GetAnimationTime(pEntity) / 2 < m_Timer)
	{
		GetSoundManager().PlaySound("ShanoaLand");
		m_IsSoundPlayed = true;
	}
}

EntityState* CrouchState::GetNextState(Entity* pEntity, float deltaTime)
{
	EntityState* pInCrouch{ InCrouchState::GetNextState(pEntity, deltaTime) };
	if (pInCrouch) return pInCrouch;

	if (!KEY_STATES[SDL_SCANCODE_S])
	{
		SetHurtHeight(pEntity, m_DefaultHurtBox.height);
		return new IdleState{ pEntity };
	}
		

	if (IsLastFrame(pEntity))
		return new CrouchedState{ pEntity };

	return nullptr;
}

CrouchedState::CrouchedState(Entity* pEntity, float slideDelay)
	: m_SlideDelay{ slideDelay }
{
	SetActiveAnimation(pEntity, "crouched");
}


void CrouchedState::Update(Entity* pEntity, float deltaTime)
{
	InCrouchState::Update(pEntity, deltaTime);
	m_Timer += deltaTime;
}

EntityState* CrouchedState::GetNextState(Entity* pEntity, float deltaTime)
{
	EntityState* pInCrouch{ InCrouchState::GetNextState(pEntity, deltaTime) };
	if (pInCrouch) return pInCrouch;

	const bool isMoving{ KEY_STATES[SDL_SCANCODE_A] || KEY_STATES[SDL_SCANCODE_D] };

	if(m_SlideDelay < m_Timer)
	{
		if (KEY_STATES[SDL_SCANCODE_S] && isMoving)
			return new SlideState{ pEntity };
	}

	if (!KEY_STATES[SDL_SCANCODE_S])
	{
		SetHurtHeight(pEntity, m_DefaultHurtBox.height);
		if(isMoving)
			return new RunState{ pEntity };
		else
			return new IdleState{ pEntity };
	}

	return nullptr;
}

SlideState::SlideState(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "slide");

	if (IsFlipped(pEntity))
		m_SlideSpeed *= -1;

	SetHurtWidth(pEntity, m_DefaultHurtBox.width * 2);
	GetSoundManager().PlaySound("ShanoaSlide");
}


void SlideState::Update(Entity* pEntity, float deltaTime)
{
	ReplenishStamina(pEntity, deltaTime);
	SetVelocityX(pEntity, m_SlideSpeed);

	if (IsLastFrame(pEntity))
		SetReverse(pEntity, true);
}

EntityState* SlideState::GetNextState(Entity* pEntity, float deltaTime)
{
	const float slideDelay{ 1 };
	if (IsReversed(pEntity) && IsLastFrame(pEntity))
	{
		SetHurtWidth(pEntity, m_DefaultHurtBox.width);
		return new CrouchedState{ pEntity, slideDelay };
	}

	return nullptr;
}