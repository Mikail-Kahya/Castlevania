#include "pch.h"
#include "PlayerState.h"
#include "InAirState.h"
#include "InCrouchState.h"
#include "myUtils.h"
#include "OnGroundState.h"
#include "Player.h"

const Uint8* PlayerState::KEY_STATES{ SDL_GetKeyboardState(nullptr) };
Uint32 PlayerState::m_MouseStates{};
Rectf PlayerState::m_DefaultHurtBox{};
bool PlayerState::m_Attacking{ false };
float PlayerState::m_StaminaDelay{};
float PlayerState::m_DodgeDelay{};

void PlayerState::Update(Entity* pEntity, float deltaTime)
{
	ReplenishStamina(pEntity, deltaTime);
	HandleMovement(pEntity);
	HandleMouse(pEntity);

	m_DodgeDelay = std::max(0.0f, m_DodgeDelay - deltaTime);
}

void PlayerState::ReplenishStamina(Entity* pEntity, float deltaTime)
{
	if (m_Attacking) return;

	Player* pPlayer{ dynamic_cast<Player*>(pEntity) };
	pPlayer->m_Stats.stamina = std::min(pPlayer->m_Stats.stamina, pPlayer->m_MaxStats.stamina);

	m_StaminaDelay -= deltaTime;
	if (m_StaminaDelay > 0) return;

	const float replenishRate{ 10 };
	pPlayer->m_Stats.stamina += replenishRate * deltaTime;
}

void PlayerState::DepleteStamina(Entity* pEntity, float amountStamina)
{
	m_StaminaDelay = 0.5f;
	dynamic_cast<Player*>(pEntity)->m_Stats.stamina -= amountStamina;
}

void PlayerState::DepleteMana(Entity* pEntity, int mana)
{
	dynamic_cast<Player*>(pEntity)->m_Stats.mana -= mana;
}

float PlayerState::GetStamina(Entity* pEntity) const
{
	return dynamic_cast<Player*>(pEntity)->m_Stats.stamina;
}

bool PlayerState::IsFalling(Entity* pEntity) const
{
	const float fallingThreshold{ -130 };
	return GetVelocity(pEntity).y < fallingThreshold;
}

bool PlayerState::IsCrouched(Entity* pEntity) const
{
	return dynamic_cast<InCrouchState*> (dynamic_cast<Player*>(pEntity)->GetState());
}

bool PlayerState::IsControlled(Entity* pEntity) const
{
	return dynamic_cast<Player*>(pEntity)->m_AllowControl;
}

void PlayerState::SetFlicker(Entity* pEntity, bool isFlickering)
{
	dynamic_cast<Player*>(pEntity)->m_IsFlickering = isFlickering;
}

bool PlayerState::SetActiveHand(Entity* pEntity, const std::string& hand)
{
	const float delay{ 0.5f };
	return dynamic_cast<Player*>(pEntity)->m_Equipment.SetActiveWeapon(hand, delay);
}

void PlayerState::DisableActiveHand(Entity* pEntity)
{
	dynamic_cast<Player*>(pEntity)->m_Equipment.DisableActiveWeapon();
}

void PlayerState::HandleMouse(Entity* pEntity)
{
	if (!IsControlled(pEntity)) return;

	if (GetStamina(pEntity) < m_StaminaCost) return;

	m_MouseStates = SDL_GetMouseState(nullptr, nullptr);

	const int left{ 1 }, right{ 4 };
	if (m_MouseStates == left)
	{
		if (SetActiveHand(pEntity, "left"))
			m_Attacking = true;
	}
	else if(m_MouseStates == right)
	{
		if (SetActiveHand(pEntity, "right"))
			m_Attacking = true;
	}
}

void PlayerState::HandleMovement(Entity* pEntity)
{
	if (!IsControlled(pEntity)) return;
	const float moveSpeed{ 200 };

	if (KEY_STATES[SDL_SCANCODE_A])
	{
		SetVelocityX(pEntity, -moveSpeed);
		SetFlip(pEntity, true);
	}
	else if (KEY_STATES[SDL_SCANCODE_D])
	{
		SetVelocityX(pEntity, moveSpeed);
		SetFlip(pEntity, false);
	}
	else
	{
		SetVelocityX(pEntity, 0);
	}
}

void PlayerState::PlayVoiceSound(const std::string& path)
{
	const int maxChance{ 100 };
	if (maxChance / 2 < myUtils::GenRand(maxChance))
		GetSoundManager().PlaySound(path + "Voice");
}

HurtState::HurtState(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "hurt");
	DisableActiveHand(pEntity);
	SetHurtWidth(pEntity, m_DefaultHurtBox.width);
	SetHurtHeight(pEntity, m_DefaultHurtBox.height);
	SetFlicker(pEntity, true);
	if (GetVelocity(pEntity).x < 0)
		m_BounceBack.x *= -1;

	const std::string soundId{ "ShanoaHurt" };
	GetSoundManager().PlaySound(soundId);
	PlayVoiceSound(soundId);
}

void HurtState::Update(Entity* pEntity, float deltaTime)
{
	m_Timer += deltaTime;

	// Gives a hop effect
	if(m_Timer < m_HurtTime / 2)
		SetVelocityY(pEntity, m_BounceBack.y);
	SetVelocityX(pEntity, m_BounceBack.x);
}

EntityState* HurtState::GetNextState(Entity* pEntity, float deltaTime)
{
	if(IsDead(pEntity))
	{
		SetFlicker(pEntity, false);
		return new DeathState{ pEntity };
	}
		

	if(m_Timer > m_HurtTime)
	{
		SetFlicker(pEntity, false);
		if(IsFalling(pEntity))
			return new FallingState{ pEntity };
		else
			return new IdleState{ pEntity };
	}

	return nullptr;
}

DeathState::DeathState(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "death");
	SetVelocityX(pEntity, 0);

	const std::string soundId{ "ShanoaDeath" };
	GetSoundManager().PlaySound(soundId);
}

void DeathState::Update(Entity* pEntity, float deltaTime)
{
	const float maxDelay{ 4 };
	m_LineDelayTimer += deltaTime;

	if(maxDelay < m_LineDelayTimer / 4 && !m_LineSpoken)
	{
		m_LineSpoken = true;
		GetSoundManager().PlaySound("ShanoaDeathLine");
	}

	if (m_LineDelayTimer > maxDelay)
		GetPlayer()->Respawn();
}

EntityState* DeathState::GetNextState(Entity* pEntity, float deltaTime)
{
	return nullptr;
}