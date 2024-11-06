#include "pch.h"
#include "Bat.h"
#include "BatState.h"

Bat::Bat(const Point2f& pivot, const EntityData& entityData)
{
	Setup("bat", pivot, entityData);
	Entity::SetState(new BatState::Idle{ this });
}

bool Bat::Hurt(const Rectf& hitBox, int damage)
{
	if(Enemy::Hurt(hitBox, damage))
	{
		m_AllowDelete = IsDead();
		SprayBlood(hitBox);
		return true;
	}
	return false;
}

void Bat::UpdateSprite(float deltaTime)
{
	m_pSprite->SetCenter(m_RigidBody.GetCenter());
	m_pSprite->Update(deltaTime);
}