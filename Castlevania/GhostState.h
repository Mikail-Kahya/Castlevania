#pragma once
#include "EnemyState.h"

namespace GhostState
{
	class Idle : public EnemyState
	{
	public:
		Idle(Entity* pEntity);
		virtual ~Idle() = default;

		Idle(const Idle& other) = delete;
		Idle& operator=(const Idle& other) = delete;
		Idle(Idle&& other) noexcept = delete;
		Idle& operator=(Idle&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		void UpdatePosition(Entity* pEntity, float deltaTime);
		void UpdateAlert(Entity* pEntity, float deltaTime);

		float m_MoveTimer{};
		float m_AlertTimer{};
		bool m_Alert{ false };
	};

	class Alert : public EnemyState
	{
	public:
		Alert(Entity* pEntity);
		virtual ~Alert() = default;

		Alert(const Alert& other) = delete;
		Alert& operator=(const Alert& other) = delete;
		Alert(Alert&& other) noexcept = delete;
		Alert& operator=(Alert&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		bool m_IsPreparing{ false };
		float m_Timer{};
	};

	class Attack : public EnemyState
	{
	public:
		Attack(Entity* pEntity);
		virtual ~Attack() = default;

		Attack(const Attack& other) = delete;
		Attack& operator=(const Attack& other) = delete;
		Attack(Attack&& other) noexcept = delete;
		Attack& operator=(Attack&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		const Point2f m_MoveFrom{};
		const Point2f m_MoveTo{};
		float m_Timer{};
	};

	class Die : public EnemyState
	{
	public:
		Die(Entity* pEntity);
		virtual ~Die() = default;

		Die(const Die& other) = delete;
		Die& operator=(const Die& other) = delete;
		Die(Die&& other) noexcept = delete;
		Die& operator=(Die&& other) noexcept = delete;

		virtual void Update(Entity* pEntity, float deltaTime) override;
		virtual EntityState* GetNextState(Entity* pEntity, float deltaTime) override { return nullptr; }
	};
}