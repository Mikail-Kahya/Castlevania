#include "pch.h"
#include "Zombie.h"
#include "ZombieState.h"

Zombie::Zombie(const Point2f& pivot, const EntityData& entityData)
{
	m_AllowHurt = false;
	Setup("zombie", pivot, entityData);
	Entity::SetState(new ZombieState::Wait{ });
}

void Zombie::Draw() const
{
	if (dynamic_cast<ZombieState::Wait*>(GetState())) return;

	if(IsHurt() || IsDead())
	{
		glColor4f(1, 0.6f, 0.6f, 1);
		Enemy::Draw();
		glColor4f(1, 1, 1, 1);
	}
	else
	{
		Enemy::Draw();
	}
}

bool Zombie::Hurt(const Rectf& hitBox, int damage)
{
	if (Enemy::Hurt(hitBox, damage))
	{
		if (IsDead())
		{
			GetSoundManager().PlaySound("ZombieDeath");
			SetState(new ZombieState::Die{ this });
		}
		else
		{
			GetSoundManager().PlaySound("ZombieHurt");
		}

		SprayBlood(hitBox);
		return true;
	}
	return false;
}