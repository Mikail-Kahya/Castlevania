#include "pch.h"
#include "OnGroundState.h"
#include "InAirState.h"
#include "InAttackState.h"
#include "InCrouchState.h"
#include "Player.h"

EntityState* OnGroundState::GetNextState(Entity* pEntity, float deltaTime)
{
	const float epsilon{ 0.005f };
	if (m_Attacking)
		return new AttackState{ pEntity };

	if(IsFalling(pEntity))
		return new FallingState{ pEntity };

	if (KEY_STATES[SDL_SCANCODE_W])
	{
		const std::string soundId{ "ShanoaJump" };
		GetSoundManager().PlaySound(soundId);
		PlayVoiceSound(soundId);
		return new JumpingState{ pEntity };
	}

	if (KEY_STATES[SDL_SCANCODE_LSHIFT] && m_DodgeDelay < epsilon)
		return new Dodge{ pEntity };
	
	return nullptr;
}

IdleState::IdleState(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "idle");

	const float epsilon{ 0.005f };
	if (m_DefaultHurtBox.height < epsilon)
		m_DefaultHurtBox = pEntity->GetHurtBox();

	m_Attacking = false;
	DisableActiveHand(pEntity);
}

EntityState* IdleState::GetNextState(Entity* pEntity, float deltaTime)
{
	EntityState* pOnGround{ OnGroundState::GetNextState(pEntity, deltaTime) };
	if (pOnGround) return pOnGround;

	if (KEY_STATES[SDL_SCANCODE_A] || KEY_STATES[SDL_SCANCODE_D])
		return new StartRunState{ pEntity };

	if (KEY_STATES[SDL_SCANCODE_S])
		return new CrouchState{ pEntity };

	if (KEY_STATES[SDL_SCANCODE_X])
		return new PowerUp{ pEntity };

	return nullptr;
}

RunState::RunState(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "run");
}


void RunState::Update(Entity* pEntity, float deltaTime)
{
	OnGroundState::Update(pEntity, deltaTime);
}

EntityState* RunState::GetNextState(Entity* pEntity, float deltaTime)
{
	EntityState* pOnGround{ OnGroundState::GetNextState(pEntity, deltaTime) };
	if (pOnGround) return pOnGround;

	if (!KEY_STATES[SDL_SCANCODE_A] && !KEY_STATES[SDL_SCANCODE_D])
		return new StopRunStop{ pEntity };
		
	if (KEY_STATES[SDL_SCANCODE_S])
		return new CrouchState{ pEntity };
	
	return nullptr;
}

StartRunState::StartRunState(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "startRun");
}

void StartRunState::Update(Entity* pEntity, float deltaTime)
{
	OnGroundState::Update(pEntity, deltaTime);
}

EntityState* StartRunState::GetNextState(Entity* pEntity, float deltaTime)
{
	EntityState* pOnGround{ OnGroundState::GetNextState(pEntity, deltaTime) };
	if (pOnGround) return pOnGround;

	if(IsLastFrame(pEntity))
		return new RunState{ pEntity };

	if(!KEY_STATES[SDL_SCANCODE_A] && !KEY_STATES[SDL_SCANCODE_D])
		return new StopRunStop{ pEntity };

	return nullptr;
}

StopRunStop::StopRunStop(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "stopRun");
}

EntityState* StopRunStop::GetNextState(Entity* pEntity, float deltaTime)
{
	EntityState* pOnGround{ OnGroundState::GetNextState(pEntity, deltaTime) };
	if (pOnGround) return pOnGround;

	if (KEY_STATES[SDL_SCANCODE_A] || KEY_STATES[SDL_SCANCODE_D])
		return new StartRunState{ pEntity };

	if(IsLastFrame(pEntity))
		return new IdleState{ pEntity };

	return nullptr;
}

HardFall::HardFall(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "hardLand");
	SetVelocityX(pEntity, 0);
}

void HardFall::Update(Entity* pEntity, float deltaTime)
{
	ReplenishStamina(pEntity, deltaTime);
	m_StuckTimer += deltaTime;
}

EntityState* HardFall::GetNextState(Entity* pEntity, float deltaTime)
{
	const float stuckTime{ 0.3f };
	if (m_StuckTimer < stuckTime) return nullptr;

	EntityState* pOnGround{ OnGroundState::GetNextState(pEntity, deltaTime) };
	if (pOnGround) return pOnGround;

	if (KEY_STATES[SDL_SCANCODE_A] || KEY_STATES[SDL_SCANCODE_D])
		return new StartRunState{ pEntity };

	if (IsLastFrame(pEntity))
		return new IdleState{ pEntity };

	return nullptr;
}

Dodge::Dodge(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "dodge");
	SetImmune(pEntity, GetAnimationTime(pEntity));
	DepleteStamina(pEntity, 5);

	const std::string soundId{ "ShanoaDodge" };
	GetSoundManager().PlaySound(soundId);
	PlayVoiceSound(soundId);
}

void Dodge::Update(Entity* pEntity, float deltaTime)
{
	float dodgeVelocity{ 300 };

	if (!IsFlipped(pEntity))
		dodgeVelocity *= -1;

	SetVelocityX(pEntity, dodgeVelocity);
}

EntityState* Dodge::GetNextState(Entity* pEntity, float deltaTime)
{
	if (IsLastFrame(pEntity))
	{
		m_DodgeDelay = 0.2f;
		return new IdleState{ pEntity };
	}

	return nullptr;
}

PowerUp::PowerUp(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "powerup");
	SetHurtWidth(pEntity, m_DefaultHurtBox.width * 1.5f);

	const std::string soundId{ "ShanoaPowerUp" };
	GetSoundManager().PlaySound(soundId);
	PlayVoiceSound(soundId);
}

void PowerUp::Update(Entity* pEntity, float deltaTime)
{
	ReplenishStamina(pEntity, deltaTime);
	HandleMovement(pEntity);
	SetVelocityX(pEntity, 0);

	if (!m_IsCharged && IsLastFrame(pEntity))
		SetActiveAnimation(pEntity, "poweredup");

	const float chargeTime{ 2.4f };
	m_ChargeTimer += deltaTime;
	if (!m_IsChargedSound && chargeTime < m_ChargeTimer)
	{
		m_IsChargedSound = true;
		GetSoundManager().PlaySound("ShanoaPowerUpCharged");
	}
}

EntityState* PowerUp::GetNextState(Entity* pEntity, float deltaTime)
{
	if (!KEY_STATES[SDL_SCANCODE_X])
	{
		ResetHurtBox(pEntity);
		GetSoundManager().StopEffects();
		return new IdleState{ pEntity };
	}
	const int maxMana{ GetPlayer()->GetMaxStats().mana };
	if (GetPlayer()->GetStats().mana < maxMana) return nullptr;

	m_MouseStates = SDL_GetMouseState(nullptr, nullptr);
	const int left{ 1 }, right{ 4 };

	if ((m_MouseStates == left || m_MouseStates == right) && SetActiveHand(pEntity, "special"))
	{
		DepleteMana(pEntity, maxMana);
		ResetHurtBox(pEntity);
		m_Attacking = true;
		return new SpecialState{ pEntity };
	}

	return nullptr;
}

void PowerUp::ResetHurtBox(Entity* pEntity)
{
	SetHurtWidth(pEntity, m_DefaultHurtBox.width);
}
