#include "pch.h"
#include "SkeletonRanged.h"
#include "SkeletonRangedState.h"
#include "Bone.h"
#include "Crumbling.h"
#include "myUtils.h"

std::vector<Part> SkeletonRanged::m_DefaultPartVec{};

SkeletonRanged::SkeletonRanged(const Point2f& pivot, const EntityData& entityData)
{
	LoadStatics();
	Setup("skeletonRanged", pivot, entityData);
	Entity::SetState(new SkeletonRangedState::Walk{ this });
}

SkeletonRanged::~SkeletonRanged()
{
	delete m_pBone;
}

void SkeletonRanged::LoadStatics()
{
	if (!m_DefaultPartVec.empty()) return;

	nlohmann::json data{};
	myUtils::ParseJson("./Enemy/Json/SkeletonRanged.json", data);

	for (const auto& object : data)
		m_DefaultPartVec.push_back(myUtils::CreatePart(object));
}

void SkeletonRanged::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if(m_pBone)
	{
		m_pBone->Update(this, deltaTime);
		if (m_pBone->AllowDelete())
		{
			delete m_pBone;
			m_pBone = nullptr;
		}
	}
}

void SkeletonRanged::Draw() const
{
	Enemy::Draw();
	if (m_pBone)
		m_pBone->Draw();
}


bool SkeletonRanged::Hurt(const Rectf& hitBox, int damage)
{
	if(Enemy::Hurt(hitBox, damage))
	{
		if (IsDead())
		{
			m_AllowDelete = true;
			GetSoundManager().PlaySound("SkeletonDeath");
			SpawnParts();
		}

		SetState(new SkeletonRangedState::Hurt{ this });
		return true;
	}
	return false;
}

bool SkeletonRanged::IsAttacking() const
{
	return dynamic_cast<SkeletonRangedState::Attack*>(GetState());
}

void SkeletonRanged::SpawnParts() const
{
	const std::string id{ "skeletonRanged" };
	const Point2f pivot{ m_RigidBody.GetPivot() };

	for (const Part& bonePart : m_DefaultPartVec)
	{
		BasicSprite* pSprite{ new BasicSprite{ GetTextureManager().GetTexture(id)} };
		pSprite->SetSrcRect(bonePart.srcRect);
		pSprite->SetScale(GetTextureManager().GetScale(id));
		pSprite->SetPivot(pivot);
		GetParticleManager().AddParticle(new Crumbling{ pivot, bonePart.velocity, pSprite });
	}
}