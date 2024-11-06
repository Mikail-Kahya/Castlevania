#pragma once
#include "EnemyState.h"
class ThrowableWeapon;

namespace ArthrovertaState
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

		void Update(Entity* pEntity, float deltaTime) override = 0;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override = 0;

	protected:
		void SetRotation(Entity* pEntity, float angle);
		void ThrowWeapon(Entity* pEntity, ThrowableWeapon* pWeapon);
		bool ActivateClaw(Entity* pEntity);
		bool ClawIsActive(Entity* pEntity);
		bool IsAttacking(Entity* pEntity);
		void BreakApart(Entity* pEntity);

		static Rectf m_DefaultHurtBox;
	};

	class Spawn : public Base
	{
	public:
		Spawn(Entity* pEntity);
		virtual ~Spawn() = default;

		Spawn(const Spawn& other) = delete;
		Spawn& operator=(const Spawn& other) = delete;
		Spawn(Spawn&& other) noexcept = delete;
		Spawn& operator=(Spawn&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		enum class State { fall, open, scream };

		void NextState(Entity* pEntity, const std::string& animId, const std::string& soundId);

		State m_State{ State::fall };
		float m_Timer{};
	};

	class Idle : public Base
	{
	public:
		Idle(Entity* pEntity, float actionDelay);
		virtual ~Idle() = default;

		Idle(const Idle& other) = delete;
		Idle& operator=(const Idle& other) = delete;
		Idle(Idle&& other) noexcept = delete;
		Idle& operator=(Idle&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		float m_ActionDelay{};
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
		float m_WalkDistance{};
	};

	class Spit : public Base
	{
	public:
		Spit(Entity* pEntity);
		virtual ~Spit() = default;

		Spit(const Spit& other) = delete;
		Spit& operator=(const Spit& other) = delete;
		Spit(Spit&& other) noexcept = delete;
		Spit& operator=(Spit&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		void ShootWeb(Entity* pEntity);
	};

	class Melee : public Base
	{
	public:
		Melee(Entity* pEntity);
		virtual ~Melee() = default;

		Melee(const Melee& other) = delete;
		Melee& operator=(const Melee& other) = delete;
		Melee(Melee&& other) noexcept = delete;
		Melee& operator=(Melee&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override {}
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;
	};

	class Shutter : public Base
	{
	public:
		Shutter(Entity* pEntity, bool open);
		virtual ~Shutter() = default;

		Shutter(const Shutter& other) = delete;
		Shutter& operator=(const Shutter& other) = delete;
		Shutter(Shutter&& other) noexcept = delete;
		Shutter& operator=(Shutter&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override {}
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		const bool m_IsOpen{};
	};

	class ChargeRoll : public Base
	{
	public:
		ChargeRoll(Entity* pEntity, bool startRoll);
		virtual ~ChargeRoll() = default;

		ChargeRoll(const ChargeRoll& other) = delete;
		ChargeRoll& operator=(const ChargeRoll& other) = delete;
		ChargeRoll(ChargeRoll&& other) noexcept = delete;
		ChargeRoll& operator=(ChargeRoll&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		bool RotatedFully() const;

		const bool m_StartRoll{};
		float m_RollVelocity{};
		float m_Angle{};
	};

	class Roll : public Base
	{
	public:
		Roll(Entity* pEntity);
		virtual ~Roll() = default;

		Roll(const Roll& other) = delete;
		Roll& operator=(const Roll& other) = delete;
		Roll(Roll&& other) noexcept = delete;
		Roll& operator=(Roll&& other) noexcept = delete;

		void Update(Entity* pEntity, float deltaTime) override;
		EntityState* GetNextState(Entity* pEntity, float deltaTime) override;

	private:
		float m_RollVelocity{ 1000 };
		int m_NrBounces{};
		float m_Angle{};
	};

	class Die : public Base
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
		float m_Timer{};
	};
}
