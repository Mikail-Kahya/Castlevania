#include "pch.h"
#include "ArthrovertaState.h"
#include "Arthroverta.h"
#include "Web.h"
#include "Explosion.h"
#include "myUtils.h"

Rectf ArthrovertaState::Base::m_DefaultHurtBox{};

void ArthrovertaState::Base::SetRotation(Entity* pEntity, float angle)
{
	dynamic_cast<Arthroverta*>(pEntity)->m_pSprite->SetRotation(angle);
}

void ArthrovertaState::Base::ThrowWeapon(Entity* pEntity, ThrowableWeapon* pWeapon)
{
	dynamic_cast<Arthroverta*>(pEntity)->m_Equipment.ThrowWeapon(pWeapon);
}

bool ArthrovertaState::Base::ActivateClaw(Entity* pEntity)
{
	return dynamic_cast<Arthroverta*>(pEntity)->m_Equipment.SetActiveWeapon("claw", 0);
}

bool ArthrovertaState::Base::ClawIsActive(Entity* pEntity)
{
	return dynamic_cast<Arthroverta*>(pEntity)->m_Equipment.GetActiveWeapon();
}

bool ArthrovertaState::Base::IsAttacking(Entity* pEntity)
{
	return dynamic_cast<Arthroverta*>(pEntity)->m_Equipment.GetActiveWeapon();
}

void ArthrovertaState::Base::BreakApart(Entity* pEntity)
{
	dynamic_cast<Arthroverta*>(pEntity)->SpawnParts();
}

ArthrovertaState::Spawn::Spawn(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "roll");
	m_DefaultHurtBox = pEntity->GetHurtBox();
}

void ArthrovertaState::Spawn::Update(Entity* pEntity, float deltaTime)
{
	const float delay{ 1 };
	const float epsilon{ 0.005f };
	switch (m_State)
	{
	case State::fall:
		if (IsGrounded(pEntity))
		{
			if (m_Timer < epsilon)
				GetSoundManager().PlaySound("ArthrovertaSpawn");
			
			m_Timer += deltaTime;
			if (delay < m_Timer)
				NextState(pEntity, "openShutter", "ArthrovertaOpenShutter");
		}
		break;
	case State::open:
		if (IsLastFrame(pEntity))
			NextState(pEntity, "scream", "ArthrovertaScream");
		break;
	case State::scream:
		if (IsLastFrame(pEntity))
			SetReverse(pEntity, true);
		break;
	}
}

EntityState* ArthrovertaState::Spawn::GetNextState(Entity* pEntity, float deltaTime)
{
	if (m_State == State::scream && IsReversed(pEntity) && IsLastFrame(pEntity))
		return new Idle{ pEntity, 1 };

	return nullptr;
}

void ArthrovertaState::Spawn::NextState(Entity* pEntity, const std::string& animId, const std::string& soundId)
{
	m_State = State(int(m_State) + 1);
	SetActiveAnimation(pEntity, animId);
	GetSoundManager().PlaySound(soundId);
}

ArthrovertaState::Idle::Idle(Entity* pEntity, float actionDelay)
	: m_ActionDelay{ actionDelay }
{
	SetActiveAnimation(pEntity, "idle");
}

void ArthrovertaState::Idle::Update(Entity* pEntity, float deltaTime)
{
	m_ActionDelay -= deltaTime;
}

EntityState* ArthrovertaState::Idle::GetNextState(Entity* pEntity, float deltaTime)
{
	if (m_ActionDelay > 0) return nullptr;

	const int maxChance{ 200 };
	const int randChance{ myUtils::GenRand(maxChance) };

	const int meleeChance{ 60 }, spitChance{ 110 }, rollChance{ 170 };

	const float meleeRange{ 200 };
	if (GetPlayerDistance(pEntity).Length() < meleeRange && randChance < meleeChance)
		return new Melee{ pEntity };

	if (randChance < spitChance)
		return new Spit{ pEntity };

	if (randChance < rollChance)
		return new Shutter{ pEntity, false };

	return new Walk{ pEntity };
}

ArthrovertaState::Walk::Walk(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "walk");
	const float maxWalkDistance{ 100 };
	m_WalkDistance = myUtils::GenRand(maxWalkDistance);
	GetSoundManager().PlaySound("ArthrovertaWalk");
}

void ArthrovertaState::Walk::Update(Entity* pEntity, float deltaTime)
{
	float walkSpeed{ 20 };
	m_WalkDistance -= walkSpeed * deltaTime;

	if (myUtils::GetRandDirection())
		walkSpeed *= -1;
	walkSpeed = (m_WalkDistance > 0) ? walkSpeed : 0;
	
	SetVelocityX(pEntity, walkSpeed);
}

EntityState* ArthrovertaState::Walk::GetNextState(Entity* pEntity, float deltaTime)
{
	if (m_WalkDistance < 0)
	{
		GetSoundManager().StopSound("ArthrovertaWalk");
		return new Idle{ pEntity, 0.5f };
	}

	return nullptr;
}

ArthrovertaState::Spit::Spit(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "scream");
}

void ArthrovertaState::Spit::Update(Entity* pEntity, float deltaTime)
{
	const bool isReversed{ IsReversed(pEntity) };
	if (IsLastFrame(pEntity) && !isReversed)
	{
		SetReverse(pEntity, !isReversed);
		ShootWeb(pEntity);
		GetSoundManager().PlaySound("ArthrovertaSpit");
	}
}

EntityState* ArthrovertaState::Spit::GetNextState(Entity* pEntity, float deltaTime)
{
	const bool isReversed{ IsReversed(pEntity) };
	if (IsLastFrame(pEntity) && isReversed)
	{
		SetReverse(pEntity, !isReversed);
		return new Idle{ pEntity, 1.5f };
	}

	return nullptr;
}

void ArthrovertaState::Spit::ShootWeb(Entity* pEntity)
{
	const Rectf hurtBox{ pEntity->GetHurtBox() };
	Point2f from{ pEntity->GetPivot() };
	from.x -= hurtBox.width / 2;
	from.y += hurtBox.height / 2;

	Point2f to{ pEntity->GetPivot() + GetPlayerDistance(pEntity) };

	ThrowWeapon(pEntity, new Web{ from, to });
}

ArthrovertaState::Melee::Melee(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "melee");
	ActivateClaw(pEntity);
	GetSoundManager().PlaySound("ArthrovertaMelee");
}

EntityState* ArthrovertaState::Melee::GetNextState(Entity* pEntity, float deltaTime)
{
	if (!ClawIsActive(pEntity))
		return new Idle{ pEntity, 1.5f };

	return nullptr;
}

ArthrovertaState::Shutter::Shutter(Entity* pEntity, bool open)
	: m_IsOpen{ open }
{
	SetActiveAnimation(pEntity, "openShutter");
	SetReverse(pEntity, !open);
	GetSoundManager().PlaySound("ArthrovertaOpenShutter");
}

EntityState* ArthrovertaState::Shutter::GetNextState(Entity* pEntity, float deltaTime)
{
	if (!IsLastFrame(pEntity)) return nullptr;

	if (m_IsOpen)
		return new Idle{ pEntity, 2 };
	else
		return new ChargeRoll{ pEntity, true };
}

ArthrovertaState::ChargeRoll::ChargeRoll(Entity* pEntity, bool startRoll)
	: m_StartRoll{ startRoll }
{
	SetActiveAnimation(pEntity, "roll");
	if (!startRoll)
	{
		m_RollVelocity = 1000;
		GetSoundManager().PlaySound("ArthrovertaOpen");
	}
		

	SetHurtWidth(pEntity, GetAnimationWidth(pEntity));
}


void ArthrovertaState::ChargeRoll::Update(Entity* pEntity, float deltaTime)
{
	const float rollAcceleration{ 500 };
	const float rollIncrease{ rollAcceleration * deltaTime };
	if (m_StartRoll)
	{
		m_RollVelocity += rollIncrease;
		m_Angle += m_RollVelocity * deltaTime;
	}
	else
	{
		m_RollVelocity -= rollIncrease;
		m_Angle -= m_RollVelocity * deltaTime;
	}

	
	if (m_StartRoll && RotatedFully())
		GetSoundManager().PlaySound("ArthrovertaCharge");
	
	SetRotation(pEntity, m_Angle);
}

EntityState* ArthrovertaState::ChargeRoll::GetNextState(Entity* pEntity, float deltaTime)
{
	const float maxVelocity{ 1000 };
	if (m_RollVelocity > maxVelocity && m_StartRoll)
		return new Roll{ pEntity };

	if (m_RollVelocity < 0 && !m_StartRoll)
	{
		SetHurtWidth(pEntity, m_DefaultHurtBox.width);
		SetHurtHeight(pEntity, m_DefaultHurtBox.height);
		SetRotation(pEntity, 0);
		return new Shutter{ pEntity, true };
	}

	return nullptr;
}

bool ArthrovertaState::ChargeRoll::RotatedFully() const
{
	const int angleDeg{ int(m_Angle * 180 / float(M_PI)) };
	const int margin{ 10 };
	return angleDeg % 360 <= margin;
}

ArthrovertaState::Roll::Roll(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "roll");
}

void ArthrovertaState::Roll::Update(Entity* pEntity, float deltaTime)
{
	const float epsilon{ 0.05f };
	if (abs(GetVelocity(pEntity).x) < epsilon)
	{
		m_RollVelocity *= -1;
		++m_NrBounces;
		GetSoundManager().PlaySound("ArthrovertaWallBounce");
	}
	m_Angle -= m_RollVelocity * deltaTime;

	SetReverse(pEntity, GetVelocity(pEntity).x < 0);
	SetVelocityX(pEntity, m_RollVelocity);
	SetRotation(pEntity, m_Angle);
}

EntityState* ArthrovertaState::Roll::GetNextState(Entity* pEntity, float deltaTime)
{
	const int maxBounces{ 9 };
	if (m_NrBounces == maxBounces)
	{
		SetVelocityX(pEntity, 0);
		return new ChargeRoll{ pEntity, false };
	}

	return nullptr;
}

ArthrovertaState::Die::Die(Entity* pEntity)
{
	SetActiveAnimation(pEntity, "scream");
	GetSoundManager().PlaySound("ArthrovertaDeath");
}

void ArthrovertaState::Die::Update(Entity* pEntity, float deltaTime)
{
	GetParticleManager().AddParticle(new Explosion{ myUtils::GetRandPointInRect(pEntity->GetHurtBox()) });
	m_Timer += deltaTime;

	const float dieDuration{ 2 };
	if (dieDuration < m_Timer)
	{
		BreakApart(pEntity);
		SetDelete(pEntity, true);
	}
}