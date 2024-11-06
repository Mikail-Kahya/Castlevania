#include "pch.h"
#include "InAirState.h"
#include "InAttackState.h"
#include "OnGroundState.h"
#include "Entity.h"

JumpingState::JumpingState(Entity* pEntity)
	: m_JumpHeight{ pEntity->GetHurtBox().height }
	, m_StartY{ pEntity->GetPivot().y }
{
	SetActiveAnimation(pEntity, "jump");
}

void JumpingState::Update(Entity* pEntity, float deltaTime)
{
	PlayerState::Update(pEntity, deltaTime);

	if(!KEY_STATES[SDL_SCANCODE_W])
	{
		m_LetGo = true;
		return;
	}

	if(GetVelocity(pEntity).y < 0)
	{
		m_LetGo = true;
		return;
	}

	if (m_StartY + m_JumpHeight < pEntity->GetPivot().y)
	{
		m_LetGo = true;
		return;
	}

	const float jumpSpeed{ 350 };
	if(!m_LetGo)
		SetVelocityY(pEntity, jumpSpeed);
}

EntityState* JumpingState::GetNextState(Entity* pEntity, float deltaTime)
{
	if(IsGrounded(pEntity))
		return new IdleState{ pEntity };

	if (m_Attacking)
		return new AirAttackState{ pEntity };

	if(IsFalling(pEntity))
		return new FallingState{ pEntity };

	return nullptr;
}

FallingState::FallingState(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "fall");
	SetHurtHeight(pEntity, m_DefaultHurtBox.height);
	DisableActiveHand(pEntity);
	m_Attacking = false;
}

void FallingState::Update(Entity* pEntity, float deltaTime)
{
	InAirState::Update(pEntity, deltaTime);
	if (!IsGrounded(pEntity))
		m_FallingVelocity = GetVelocity(pEntity).y;
}

EntityState* FallingState::GetNextState(Entity* pEntity, float deltaTime)
{
	if(IsGrounded(pEntity))
	{
		const float hardFallThreshold{ 800 };

		GetSoundManager().PlaySound("ShanoaLand");

		if (abs(m_FallingVelocity) > hardFallThreshold)
		{
			return new HardFall{ pEntity };
		}

		return new StopRunStop{ pEntity };
	}

	if (m_Attacking)
		return new AirAttackState{ pEntity };

	return nullptr;
}
