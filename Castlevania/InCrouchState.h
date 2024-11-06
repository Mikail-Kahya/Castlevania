#pragma once
#include "OnGroundState.h"

class InCrouchState : public OnGroundState
{
public:
	InCrouchState() = default;
	virtual ~InCrouchState() = default;

	InCrouchState(const InCrouchState& other) = delete;
	InCrouchState& operator=(const InCrouchState& other) = delete;
	InCrouchState(InCrouchState&& other) noexcept = delete;
	InCrouchState& operator=(InCrouchState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
};

class CrouchState : public InCrouchState
{
public:
	explicit CrouchState(Entity* pEntity);
	virtual ~CrouchState() = default;

	CrouchState(const CrouchState& other) = delete;
	CrouchState& operator=(const CrouchState& other) = delete;
	CrouchState(CrouchState&& other) noexcept = delete;
	CrouchState& operator=(CrouchState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

private:
	bool m_IsSoundPlayed{ false };
	float m_Timer{};
};

class CrouchedState : public InCrouchState
{
public:
	explicit CrouchedState(Entity* pEntity, float slideDelay = 0);
	virtual ~CrouchedState() = default;

	CrouchedState(const CrouchedState& other) = delete;
	CrouchedState& operator=(const CrouchedState& other) = delete;
	CrouchedState(CrouchedState&& other) noexcept = delete;
	CrouchedState& operator=(CrouchedState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

private:
	const float m_SlideDelay{};
	float m_Timer{};
};

class SlideState : public InCrouchState
{
public:
	explicit SlideState(Entity* pEntity);
	virtual ~SlideState() = default;

	SlideState(const SlideState& other) = delete;
	SlideState& operator=(const SlideState& other) = delete;
	SlideState(SlideState&& other) noexcept = delete;
	SlideState& operator=(SlideState&& other) noexcept = delete;

	void Update(Entity* pEntity, float deltaTime) override;
	EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

private:
	float m_SlideSpeed{ 325.0f };
	bool m_IsReturning{ false };
};