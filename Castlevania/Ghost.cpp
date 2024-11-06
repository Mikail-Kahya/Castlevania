#include "pch.h"
#include "Ghost.h"
#include "GhostState.h"
#include "Level.h"

Ghost::Ghost(const Point2f& pivot, const EntityData& entityData)
{
	Setup("ghost", pivot, entityData);
	Entity::SetState(new GhostState::Idle{ this });
}

void Ghost::Update(float deltaTime)
{
	if (m_TravelBounds.width <= 0)
		m_TravelBounds = Level::GetBounds();
	Enemy::Update(deltaTime);
}

void Ghost::Draw() const
{
	if (IsHurt())
	{
		glColor4f(1, 0.8f, 0.8f, 1);
		Enemy::Draw();
		glColor4f(1, 1, 1, 1);
	}
	else
	{
		Enemy::Draw();
	}
}

bool Ghost::Hurt(const Rectf& hitBox, int damage)
{
	if(Enemy::Hurt(hitBox, damage))
	{
		SetState(new GhostState::Die{ this });
		return true;
	}
	else
	{
		return false;
	}
}

void Ghost::UpdateRigidBody(float deltaTime)
{
	m_RigidBody.SetPivot(m_RigidBody.GetPivot() + m_RigidBody.GetVelocity() * deltaTime);
}

void Ghost::UpdateSprite(float deltaTime)
{
	m_pSprite->SetCenter(m_RigidBody.GetCenter());
	m_pSprite->Update(deltaTime);
}
