#pragma once
#include "PlayerState.h"

class OnGroundState : public PlayerState
{
public:
	OnGroundState() = default;
	virtual ~OnGroundState() = default;

	OnGroundState(const OnGroundState& other) = delete;
	OnGroundState& operator=(const OnGroundState& other) = delete;
	OnGroundState(OnGroundState&& other) noexcept = delete;
	OnGroundState& operator=(OnGroundState&& other) noexcept = delete;

	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
};

class IdleState : public OnGroundState
{
public:
	explicit IdleState(Entity* pEntity);
	virtual ~IdleState() = default;

	IdleState(const IdleState& other) = delete;
	IdleState& operator=(const IdleState& other) = delete;
	IdleState(IdleState&& other) noexcept = delete;
	IdleState& operator=(IdleState&& other) noexcept = delete;

	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
};

class RunState : public OnGroundState
{
public:
	explicit RunState(Entity* pEntity);
	virtual ~RunState() = default;

	RunState(const RunState& other) = delete;
	RunState& operator=(const RunState& other) = delete;
	RunState(RunState&& other) noexcept = delete;
	RunState& operator=(RunState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
};

class StartRunState : public OnGroundState
{
public:
	explicit StartRunState(Entity* pEntity);
	virtual ~StartRunState() = default;

	StartRunState(const StartRunState& other) = delete;
	StartRunState& operator=(const StartRunState& other) = delete;
	StartRunState(StartRunState&& other) noexcept = delete;
	StartRunState& operator=(StartRunState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
};

class StopRunStop : public OnGroundState
{
public:
	explicit StopRunStop(Entity* pEntity);
	virtual ~StopRunStop() = default;

	StopRunStop(const StopRunStop& other) = delete;
	StopRunStop& operator=(const StopRunStop& other) = delete;
	StopRunStop(StopRunStop&& other) noexcept = delete;
	StopRunStop& operator=(StopRunStop&& other) noexcept = delete;

	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
};

class HardFall : public OnGroundState
{
public:
	explicit HardFall(Entity* pEntity);
	virtual ~HardFall() = default;

	HardFall(const HardFall& other) = delete;
	HardFall& operator=(const HardFall& other) = delete;
	HardFall(HardFall&& other) noexcept = delete;
	HardFall& operator=(HardFall&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

private:
	float m_StuckTimer{};
};

class Dodge : public OnGroundState
{
public:
	explicit Dodge(Entity* pEntity);
	virtual ~Dodge() = default;

	Dodge(const Dodge& other) = delete;
	Dodge& operator=(const Dodge& other) = delete;
	Dodge(Dodge&& other) noexcept = delete;
	Dodge& operator=(Dodge&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
};

class PowerUp : public OnGroundState
{
public:
	explicit PowerUp(Entity* pEntity);
	virtual ~PowerUp() = default;

	PowerUp(const PowerUp& other) = delete;
	PowerUp& operator=(const PowerUp& other) = delete;
	PowerUp(PowerUp&& other) noexcept = delete;
	PowerUp& operator=(PowerUp&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

private:
	void ResetHurtBox(Entity* pEntity);

	bool m_IsCharged{ false };
	bool m_IsChargedSound{ false };
	float m_ChargeTimer{};
};