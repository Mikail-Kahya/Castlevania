#pragma once
#include "EnemyState.h"
namespace BatState
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
		const float m_AlertDistance{ 300 };

		bool m_Alert{ false };

	};

	class AlertState : public EnemyState
	{
	public:
		AlertState(Entity* pEntity);
		virtual ~AlertState() = default;

		AlertState(const AlertState& other) = delete;
		AlertState& operator=(const AlertState& other) = delete;
		AlertState(AlertState&& other) noexcept = delete;
		AlertState& operator=(AlertState&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		const float m_AlertDistance{ 400 };
		const float m_AttackTime{ 2 };
		float m_Timer{};
		bool m_Attack{ false };
		bool m_OutOfRange{ false };

	};

	class AttackState : public EnemyState
	{
	public:
		AttackState(Entity* pEntity, const Vector2f& distance);
		virtual ~AttackState() = default;

		AttackState(const AttackState& other) = delete;
		AttackState& operator=(const AttackState& other) = delete;
		AttackState(AttackState&& other) noexcept = delete;
		AttackState& operator=(AttackState&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		const Point2f m_Origin{};
		float m_Intercept{};
		int m_Direction{};
	};
}