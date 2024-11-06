#pragma once
#include "EnemyState.h"
namespace BansheeState
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
		bool m_InRange{ false };
		bool m_UsedSound{ false };
		float m_Opacity{ 0 };
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

		void Update(Entity* pEntity, float deltaTime) override {}
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
	};

	class Move : public EnemyState
	{
	public:
		Move(Entity* pEntity);
		virtual ~Move() = default;

		Move(const Move& other) = delete;
		Move& operator=(const Move& other) = delete;
		Move(Move&& other) noexcept = delete;
		Move& operator=(Move&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
	};

	class AttackStart : public EnemyState
	{
	public:
		AttackStart(Entity* pEntity);
		virtual ~AttackStart() = default;

		AttackStart(const AttackStart& other) = delete;
		AttackStart& operator=(const AttackStart& other) = delete;
		AttackStart(AttackStart&& other) noexcept = delete;
		AttackStart& operator=(AttackStart&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override {}
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
	};

	class AttackEnd : public EnemyState
	{
	public:
		AttackEnd(Entity* pEntity);
		virtual ~AttackEnd() = default;

		AttackEnd(const AttackEnd& other) = delete;
		AttackEnd& operator=(const AttackEnd& other) = delete;
		AttackEnd(AttackEnd&& other) noexcept = delete;
		AttackEnd& operator=(AttackEnd&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override {}
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
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

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override { return nullptr; }

	private:
		float m_Opacity{ 1 };
	};
}