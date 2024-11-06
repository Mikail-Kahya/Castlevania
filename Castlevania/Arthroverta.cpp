#include "pch.h"
#include "Arthroverta.h"
#include "myUtils.h"
#include "ThrowableWeapon.h"
#include "ArthrovertaClaw.h"
#include "Exploding.h"
#include "Dust.h"

bool Arthroverta::m_BossDefeated{ false };

Arthroverta::Arthroverta(const Point2f& pivot, const EntityData& entityData)
{
	m_AllowDelete = m_BossDefeated;
	if (m_AllowDelete) return;

	Setup("arthroverta", pivot, entityData);
	Entity::SetState(new ArthrovertaState::Spawn{ this });
	m_Equipment.AddWeapon("claw", new ArthrovertaClaw{ pivot, entityData.stats.damage });
}

void Arthroverta::Update(float deltaTime)
{
	if (m_AllowDelete) return;
	Enemy::Update(deltaTime);
	m_Equipment.Update(this, deltaTime);
	UpdateRoll(deltaTime);
}

void Arthroverta::Draw() const
{
	if (m_AllowDelete) return;
	Enemy::Draw();
	m_Equipment.Draw();
}

bool Arthroverta::Hurt(const Rectf& hitBox, int damage)
{
	if (m_AllowDelete) return false;
	if(Enemy::Hurt(hitBox, damage))
	{
		if (IsDead())
		{
			SetState(new ArthrovertaState::Die{ this });
			m_BossDefeated = true;
		}

		return true;
	}
	return false;
}

void Arthroverta::SpawnParts() const
{
	const std::string id{ "arthroverta" };
	const Point2f bottomLeft{ m_pSprite->GetPosition() };
	Texture* pTexture{ GetTextureManager().GetTexture(id) };
	const float scale{ GetTextureManager().GetScale(id) };


	nlohmann::json data{};
	myUtils::ParseJson("./Enemy/Json/Arthroverta.json", data);

	for (const auto& partData : data)
	{
		const Part bodyPart{ myUtils::CreatePart(partData) };
		const Point2f pivot{ bottomLeft + bodyPart.offset * scale };
		BasicSprite* pSprite{ new BasicSprite{ pTexture, Point2f{}, scale } };
		pSprite->SetSrcRect(bodyPart.srcRect);

		GetParticleManager().AddParticle(new Exploding{ pivot, bodyPart.velocity, pSprite });
	}
}

void Arthroverta::UpdateRoll(float deltaTime)
{
	if (!IsRolling()) return;
	m_RollDustTimer -= deltaTime;
	if (m_RollDustTimer < 0)
	{
		const float rollDustDelay{ 0.02f };
		const float dustScale{ 1.5f };

		GetParticleManager().AddParticle(new Dust{ m_RigidBody.GetPivot(), dustScale });

		m_RollDustTimer = rollDustDelay;
	}
}

bool Arthroverta::IsAttacking() const
{
	return dynamic_cast<ArthrovertaState::Spit*>(GetState());
}

bool Arthroverta::IsRolling() const
{
	return dynamic_cast<ArthrovertaState::Roll*>(GetState());
}