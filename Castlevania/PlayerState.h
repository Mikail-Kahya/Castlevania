#pragma once
#include "EntityState.h"
#include <Vector2f.h>

class PlayerState : public EntityState
{
public:
	PlayerState() = default;
	virtual ~PlayerState() = default;

	PlayerState(const PlayerState& other) = delete;
	PlayerState& operator=(const PlayerState& other) = delete;
	PlayerState(PlayerState&& other) noexcept = delete;
	PlayerState& operator=(PlayerState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	virtual EntityState* GetNextState(Entity* pEntity, float deltaTime) = 0;

protected:
	void ReplenishStamina(Entity* pEntity, float deltaTime);
	void DepleteStamina(Entity* pEntity, float amountStamina);
	void DepleteMana(Entity* pEntity, int mana);
	float GetStamina(Entity* pEntity) const;
	bool IsFalling(Entity* pEntity) const;
	bool IsCrouched(Entity* pEntity) const;
	bool IsControlled(Entity* pEntity) const;

	void SetFlicker(Entity* pEntity, bool isFlickering);
	bool SetActiveHand(Entity* pEntity, const std::string& hand);
	void DisableActiveHand(Entity* pEntity);

	void HandleMouse(Entity* pEntity);
	void HandleMovement(Entity* pEntity);

	void PlayVoiceSound(const std::string& path);

	static const Uint8* KEY_STATES;
	static Uint32 m_MouseStates;
	static Rectf m_DefaultHurtBox;
	static float m_StaminaDelay;
	static bool m_Attacking;
	static float m_DodgeDelay;
	const float m_StaminaCost{ 2 };
};

class HurtState : public PlayerState
{
public:
	HurtState(Entity* pEntity);
	virtual ~HurtState() = default;

	HurtState(const HurtState& other) = delete;
	HurtState& operator=(const HurtState& other) = delete;
	HurtState(HurtState&& other) noexcept = delete;
	HurtState& operator=(HurtState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

private:
	Vector2f m_BounceBack{ -50, 100 };
	const float m_HurtTime{ 0.5f };
	float m_Timer{};
};

class DeathState : public PlayerState
{
public:
	DeathState(Entity* pEntity);
	virtual ~DeathState() = default;

	DeathState(const DeathState& other) = delete;
	DeathState& operator=(const DeathState& other) = delete;
	DeathState(DeathState&& other) noexcept = delete;
	DeathState& operator=(DeathState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

private:
	float m_LineDelayTimer{};
	bool m_LineSpoken{ false };
};