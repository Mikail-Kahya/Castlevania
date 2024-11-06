#pragma once
#include "EnemyState.h"

namespace SkeletonRangedState
{
	class Base : public EnemyState
	{
	public:
		Base() = default;
		virtual ~Base() = default;

		Base(const Base& other) = delete;
		Base& operator=(const Base& other) = delete;
		Base(Base&& other) noexcept = delete;
		Base& operator=(Base&& other) noexcept = delete;

		virtual void Update(Entity* pEntity, float deltaTime) = 0;
		virtual EntityState* GetNextState(Entity* pEntity, float deltaTime) = 0;

	protected:
		void ThrowBone(Entity* pEntity);
		bool IsAttackReady(Entity* pEntity) const;
		int GetDamage(Entity* pEntity) const;
	};

	class Walk : public Base
	{
	public:
		Walk(Entity* pEntity);
		virtual ~Walk() = default;

		Walk(const Walk& other) = delete;
		Walk& operator=(const Walk& other) = delete;
		Walk(Walk&& other) noexcept = delete;
		Walk& operator=(Walk&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		const float m_MinDistance{ 20 };
		const float m_MaxDistance{ 150 };
		float m_Distance{};
		int m_Direction{};
	};

	class Jump : public Base
	{
	public:
		Jump(Entity* pEntity);
		virtual ~Jump() = default;

		Jump(const Jump& other) = delete;
		Jump& operator=(const Jump& other) = delete;
		Jump(Jump&& other) noexcept = delete;
		Jump& operator=(Jump&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override {}
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
	};

	class Land : public Base
	{
	public:
		Land(Entity* pEntity);
		virtual ~Land() = default;

		Land(const Land& other) = delete;
		Land& operator=(const Land& other) = delete;
		Land(Land&& other) noexcept = delete;
		Land& operator=(Land&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override {}
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
	};

	class Attack : public Base
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
		const float m_ThrowDelay{ 0.5f };
		float m_Timer{};
	};

	class Hurt : public Base
	{
	public:
		Hurt(Entity* pEntity);
		virtual ~Hurt() = default;

		Hurt(const Hurt& other) = delete;
		Hurt& operator=(const Hurt& other) = delete;
		Hurt(Hurt&& other) noexcept = delete;
		Hurt& operator=(Hurt&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override {}
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
	};
}