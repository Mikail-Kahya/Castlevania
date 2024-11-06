#include "pch.h"
#include "EntityState.h"
#include "Entity.h"

const Stats& EntityState::GetStats(Entity* pEntity) const
{
	return pEntity->m_Stats;
}

const Vector2f& EntityState::GetVelocity(Entity* pEntity) const
{
	return pEntity->m_RigidBody.GetVelocity();
}

float EntityState::GetAnimationTime(Entity* pEntity) const
{
	return pEntity->m_pSprite->GetAnimationTime();
}

int EntityState::GetDirection(Entity* pEntity) const
{
	return (IsFlipped(pEntity)) ? -1 : 1;
}

float EntityState::GetAnimationWidth(Entity* pEntity) const
{
	return pEntity->m_pSprite->GetWidth();
}

float EntityState::GetAnimationHeight(Entity* pEntity) const
{
	return pEntity->m_pSprite->GetHeight();
}

bool EntityState::IsLastFrame(Entity* pEntity) const
{
	return pEntity->m_pSprite->IsLastFrame();
}

bool EntityState::IsHurt(Entity* pEntity) const
{
	return pEntity->IsHurt();
}

bool EntityState::IsDead(Entity* pEntity) const
{
	return pEntity->IsDead();
}

bool EntityState::IsFlipped(Entity* pEntity) const
{
	return pEntity->m_pSprite->IsFlipped();
}

bool EntityState::IsReversed(Entity* pEntity) const
{
	return pEntity->m_pSprite->IsReversed();
}

bool EntityState::IsGrounded(Entity* pEntity) const
{
	return pEntity->m_RigidBody.IsGrounded();
}

void EntityState::SetVelocityX(Entity* pEntity, float x)
{
	const Vector2f velocity{ pEntity->m_RigidBody.GetVelocity() };
	pEntity->m_RigidBody.SetVelocity(Vector2f{ x, velocity.y });
}

void EntityState::SetVelocityY(Entity* pEntity, float y)
{
	const Vector2f velocity{ pEntity->m_RigidBody.GetVelocity() };
	pEntity->m_RigidBody.SetVelocity(Vector2f{ velocity.x, y });
}

void EntityState::SetVelocity(Entity* pEntity, const Vector2f& velocity)
{
	pEntity->m_RigidBody.SetVelocity(velocity);
}

void EntityState::SetHurtWidth(Entity* pEntity, float width)
{
	pEntity->m_RigidBody.SetWidth(width);
}

void EntityState::SetHurtHeight(Entity* pEntity, float height)
{
	pEntity->m_RigidBody.SetHeight(height);
}

void EntityState::SetActiveAnimation(Entity* pEntity, const std::string& id)
{
	pEntity->m_pSprite->SetActiveAnimation(id);
}

void EntityState::SetFlip(Entity* pEntity, bool isFlipped)
{
	pEntity->m_pSprite->SetFlip(isFlipped);
}

void EntityState::SetReverse(Entity* pEntity, bool isReversed)
{
	pEntity->m_pSprite->SetReverse(isReversed);
}

void EntityState::SetSpritePivot(Entity* pEntity, const Point2f& pivot)
{
	pEntity->m_pSprite->SetPivot(pivot);
}

void EntityState::SetRigidPivot(Entity* pEntity, const Point2f& pivot)
{
	pEntity->m_RigidBody.SetPivot(pivot);
}

void EntityState::SetImmune(Entity* pEntity, float immuneTime)
{
	pEntity->m_ImmuneTimer = immuneTime;
}
