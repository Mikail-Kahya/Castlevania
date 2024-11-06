#include "pch.h"
#include "debugPch.h"
#include "Entity.h"
#include "EntityState.h"
#include "BloodSplatter.h"
#include "DamageNumber.h"
#include "myUtils.h"

Entity::~Entity()
{
	delete m_pSprite;
	delete m_pState;
}

void Entity::Setup(const std::string& id, const Point2f& pivot, const EntityData& entityData)
{
	m_RigidBody = RigidBody{ pivot, entityData.width, entityData.height };
	m_Stats = entityData.stats;
	m_pSprite = dynamic_cast<Avatar*> (GetTextureManager().CreateSprite(id));
}

void Entity::Update(float deltaTime)
{
	UpdateState(deltaTime);
	UpdateRigidBody(deltaTime);
	UpdateSprite(deltaTime);
	if (IsHurt())
		m_ImmuneTimer -= deltaTime;
	UpdateFlicker(deltaTime);
}

void Entity::Draw() const
{
	m_pSprite->Draw();

#ifdef _DEBUG_COMBAT
	glColor4f(0, 1, 0, 1);
	utils::DrawRect(m_RigidBody.GetHurtBox());
	glColor4f(1, 1, 1, 1); 
#endif
}

void Entity::UpdateState(float deltaTime)
{
	EntityState* pNextState{ m_pState->GetNextState(this, deltaTime) };
	if (pNextState)
	{
		delete m_pState;
		m_pState = pNextState;
	}
	m_pState->Update(this, deltaTime);
}

void Entity::UpdateSprite(float deltaTime)
{
	m_pSprite->SetPivot(m_RigidBody.GetPivot());
	m_pSprite->Update(deltaTime);
}

void Entity::UpdateRigidBody(float deltaTime)
{
	m_RigidBody.UpdatePhysics(deltaTime);
	m_RigidBody.CollideHard();
}

void Entity::SprayBlood(const Rectf& hitBox) const
{
	const Point2f pivot{ m_RigidBody.GetPivot() };
	const Point2f bottomLeft{ pivot.x, pivot.y + m_RigidBody.GetHurtBox().height / 2 };

	SprayBlood(hitBox, bottomLeft);
}

void Entity::SprayBlood(const Rectf& hitBox, const Point2f& bottomLeft) const
{
	const float hitBoxCenter{ hitBox.left + hitBox.width / 2 };
	BloodSplatter* pBloodSplatter{ new BloodSplatter{ bottomLeft } };
	if (hitBoxCenter > m_RigidBody.GetPivot().x)
		pBloodSplatter->Flip();

	GetParticleManager().AddParticle(pBloodSplatter);
}

void Entity::SpawnDamage(int damage, const Color4f& color)
{
	const Point2f pivot{ myUtils::GetRandPointInRect(m_RigidBody.GetHurtBox()) };
	GetParticleManager().AddParticle(new DamageNumber{ pivot, damage, color });
}

bool Entity::Hurt(const Rectf& hitBox, int damage)
{
	if ( IsDead() || IsHurt()) return false;
	if(utils::IsOverlapping(hitBox, m_RigidBody.GetHurtBox()))
	{
		m_ImmuneTimer = m_ImmuneTime;
		m_Stats.hp -= damage - m_Stats.defense;
		m_Stats.hp = std::max(0, m_Stats.hp);
		return true;
	}
	return false;
}

Rectf Entity::GetHurtBox() const
{
	return m_RigidBody.GetHurtBox();
}

const Point2f& Entity::GetPivot() const
{
	return m_RigidBody.GetPivot();
}

bool Entity::IsDead() const
{
	return m_Stats.hp <= 0;
}

bool Entity::IsHurt() const
{
	return m_ImmuneTimer > 0;
}

bool Entity::IsFlickering() const
{
	return m_FlickerTimer > 0;
}

void Entity::UpdateFlicker(float deltaTime)
{
	if (!m_IsFlickering)
	{
		m_FlickerTimer = 0;
		return;
	}

	m_FlickerTimer -= deltaTime;

	const float flickerTime{ 0.1f };
	if (m_FlickerTimer < -flickerTime)
		m_FlickerTimer = flickerTime;
}

void Entity::SetState(EntityState* pState)
{
	delete m_pState;
	m_pState = pState;
}

void Entity::SetImmuneTime(float immuneTime)
{
	m_ImmuneTime = immuneTime;
}

EntityState* Entity::GetState() const
{
	return m_pState;
}
