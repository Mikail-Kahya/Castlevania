#pragma once
#include "PlayerState.h"

class Player;

class InAttackState : public PlayerState
{
public:
	InAttackState(Entity* pEntity, const std::string& state);
	virtual ~InAttackState() = default;

	InAttackState(const InAttackState& other) = delete;
	InAttackState& operator=(const InAttackState& other) = delete;
	InAttackState(InAttackState&& other) noexcept = delete;
	InAttackState& operator=(InAttackState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	virtual EntityState* GetNextState(Entity* pEntity, float deltaTime) = 0;

protected:
	void PlayAttackVoice();
	void PlayAttack();
	void StopAttack(Entity* pEntity);

	bool m_Finished{ false };
};

class CrouchAttackState : public InAttackState
{
public:
	CrouchAttackState(Entity* pEntity);
	virtual ~CrouchAttackState() = default;

	CrouchAttackState(const CrouchAttackState& other) = delete;
	CrouchAttackState& operator=(const CrouchAttackState& other) = delete;
	CrouchAttackState(CrouchAttackState&& other) noexcept = delete;
	CrouchAttackState& operator=(CrouchAttackState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
};

class AttackState : public InAttackState
{
public:
	AttackState(Entity* pEntity);
	virtual ~AttackState() = default;

	AttackState(const AttackState& other) = delete;
	AttackState& operator=(const AttackState& other) = delete;
	AttackState(AttackState&& other) noexcept = delete;
	AttackState& operator=(AttackState&& other) noexcept = delete;

	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
};

class AirAttackState : public InAttackState
{
public:
	AirAttackState(Entity* pEntity);
	virtual ~AirAttackState() = default;

	AirAttackState(const AirAttackState& other) = delete;
	AirAttackState& operator=(const AirAttackState& other) = delete;
	AirAttackState(AirAttackState&& other) noexcept = delete;
	AirAttackState& operator=(AirAttackState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
};

class SpecialState : public InAttackState
{
public:
	SpecialState(Entity* pEntity);
	virtual ~SpecialState() = default;

	SpecialState(const SpecialState& other) = delete;
	SpecialState& operator=(const SpecialState& other) = delete;
	SpecialState(SpecialState&& other) noexcept = delete;
	SpecialState& operator=(SpecialState&& other) noexcept = delete;

	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
};
