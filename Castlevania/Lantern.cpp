#include "pch.h"
#include "Lantern.h"
#include "Mana.h"
#include "Exploding.h"
#include "myUtils.h"

const Rectf Lantern::m_DefaultHurtBox{ 0, 0, 30, 60 };
std::vector<Part> Lantern::m_DefaultPartVec{};

Lantern::Lantern(const Point2f& pivot)
{
	LoadStatics();
	Setup(pivot);
}

void Lantern::Setup(const Point2f& pivot)
{
	m_HurtBox = m_DefaultHurtBox;
	SetRigidPivot(pivot);

	m_pSprite = GetTextureManager().CreateSprite("lantern");
	dynamic_cast<AnimatedSprite*>(m_pSprite)->SetPivot(pivot);
}

void Lantern::Update(float deltaTime)
{
	m_pSprite->Update(deltaTime);
}

PickUp* Lantern::SpawnPickUp() const
{
	const float middle{ m_HurtBox.left + m_HurtBox.width / 2 };
	const float top{ m_HurtBox.bottom + m_HurtBox.height };

	return new Mana{ Point2f(middle, top) };
}

void Lantern::LoadStatics()
{
	if (!m_DefaultPartVec.empty()) return;

	nlohmann::json data{};
	myUtils::ParseJson("./Destructable/Json/Lantern.json", data);

	for (const auto& object : data)
		m_DefaultPartVec.push_back(myUtils::CreatePart(object));
}

bool Lantern::Hurt(const Rectf& hitBox)
{
	if(Destructable::Hurt(hitBox))
	{
		m_AllowDelete = true;
		SpawnParts();
		return true;
	}
	return false;
}

void Lantern::SpawnParts()
{
	const std::string id{ "lantern" };
	const Point2f pivot{ m_HurtBox.left + m_HurtBox.width / 2,
						m_HurtBox.bottom + m_HurtBox.height / 2 };

	for (const Part& lanternPart : m_DefaultPartVec)
	{
		BasicSprite* pSprite{ new BasicSprite{ GetTextureManager().GetTexture(id)}};
		pSprite->SetSrcRect(lanternPart.srcRect);
		pSprite->SetScale(GetTextureManager().GetScale(id));
		pSprite->SetPivot(pivot);
		GetParticleManager().AddParticle(new Exploding{ pivot, lanternPart.velocity, pSprite });
	}
	GetSoundManager().PlaySound("LanternBreak");
}
