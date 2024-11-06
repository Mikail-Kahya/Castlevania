#include "pch.h"
#include "Banshee.h"
#include "BansheeScream.h"
#include "BansheeState.h"

Banshee::Banshee(const Point2f& pivot, const EntityData& entityData)
{
	Setup("banshee", pivot, entityData);
	Entity::SetState(new BansheeState::Idle{ this });
	m_pWeapon = new BansheeScream{ m_RigidBody.GetPivot(), entityData.stats.damage };
}

Banshee::~Banshee()
{
	delete m_pWeapon;
}

void Banshee::Update(float deltaTime)
{
	Enemy::Update(deltaTime);
	if (IsAttacking())
		m_pWeapon->Update(this, deltaTime);
}

void Banshee::Draw() const
{
	if (IsAttacking())
		m_pWeapon->Draw();
	glColor4f(1, 1, 1, m_Opacity);
	Enemy::Draw();
	glColor4f(1, 1, 1, 1);
}

bool Banshee::Hurt(const Rectf& hitBox, int damage)
{
	if(Enemy::Hurt(hitBox, damage))
	{
		if (IsDead())
			SetState(new BansheeState::Die{ this });
		return true;
	}
	return false;
}

void Banshee::SetOpacity(float opacity)
{
	m_Opacity = opacity;
}

bool Banshee::IsAttacking() const
{
	return dynamic_cast<BansheeState::Attack*>(GetState());
}

void Banshee::UpdateRigidBody(float deltaTime)
{
	m_RigidBody.SetPivot(m_RigidBody.GetPivot() + m_RigidBody.GetVelocity() * deltaTime);
}

void Banshee::UpdateSprite(float deltaTime)
{
	m_pSprite->SetCenter(m_RigidBody.GetCenter());
	m_pSprite->Update(deltaTime);
}
