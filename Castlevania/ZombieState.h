#pragma once
#include "EnemyState.h"

namespace ZombieState
{
	class Wait : public EnemyState
	{
	public:
		Wait();
		virtual ~Wait() = default;

		Wait(const Wait& other) = delete;
		Wait& operator=(const Wait& other) = delete;
		Wait(Wait&& other) noexcept = delete;
		Wait& operator=(Wait&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		bool m_IsWaiting{ true };
		float m_SpawnTimer{};
	};

	class Rise : public EnemyState
	{
	public:
		Rise(Entity* pEntity);
		virtual ~Rise() = default;

		Rise(const Rise& other) = delete;
		Rise& operator=(const Rise& other) = delete;
		Rise(Rise&& other) noexcept = delete;
		Rise& operator=(Rise&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override {};
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
	};

	class Walk : public EnemyState
	{
	public:
		Walk(Entity* pEntity);
		virtual ~Walk() = default;

		Walk(const Walk& other) = delete;
		Walk& operator=(const Walk& other) = delete;
		Walk(Walk&& other) noexcept = delete;
		Walk& operator=(Walk&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override { return nullptr; }
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
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override { return nullptr; };

	private:
		void SprayBlood(Entity* pEntity, float deltaTime);

		float m_Timer{};
	};
}