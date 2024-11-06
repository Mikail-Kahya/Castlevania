#pragma once
#include "PlayerState.h"

class InAirState : public PlayerState
{
public:
	InAirState() = default;
	virtual ~InAirState() = default;

	InAirState(const InAirState& other) = delete;
	InAirState& operator=(const InAirState& other) = delete;
	InAirState(InAirState&& other) noexcept = delete;
	InAirState& operator=(InAirState&& other) noexcept = delete;
};

class JumpingState : public InAirState
{
public:
	JumpingState(Entity* pEntity);
	virtual ~JumpingState() = default;

	JumpingState(const JumpingState& other) = delete;
	JumpingState& operator=(const JumpingState& other) = delete;
	JumpingState(JumpingState&& other) noexcept = delete;
	JumpingState& operator=(JumpingState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

private:
	float m_JumpHeight{};
	float m_StartY{};
	bool m_LetGo{ false };
};

class FallingState : public InAirState
{
public:
	FallingState(Entity* pEntity);
	virtual ~FallingState() = default;

	FallingState(const FallingState& other) = delete;
	FallingState& operator=(const FallingState& other) = delete;
	FallingState(FallingState&& other) noexcept = delete;
	FallingState& operator=(FallingState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

private:
	float m_FallingVelocity{};
};
