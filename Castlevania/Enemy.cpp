#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
{
	SetImmuneTime(0.4f);
}

void Enemy::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	if (!IsDead() && m_AllowHurt)
		GetPlayer()->Hurt(m_RigidBody.GetHurtBox(), m_Stats.damage);
	m_IsFlickering = IsHurt();
}

void Enemy::Draw() const
{
	if (IsFlickering())
		DrawFlicker();
	else
		Entity::Draw();
}

bool Enemy::Hurt(const Rectf& hitBox, int damage)
{
	if (!m_AllowHurt) return false;
	if (Entity::Hurt(hitBox, damage))
	{
		GetSoundManager().PlaySound("EnemyHit");
		SpawnDamage(damage - m_Stats.defense, Color4f{ 1,1,1,1 });
;		return true;
	}

	return false;
}

bool Enemy::AllowDelete() const
{
	return m_AllowDelete;
}

int Enemy::GetExp() const
{
	return m_Stats.exp;
}

void Enemy::DrawFlicker() const
{
	glColor4f(0.5f, 0, 0, 1);
	m_pSprite->Draw();
	glColor4f(1, 1, 1, 1);
}