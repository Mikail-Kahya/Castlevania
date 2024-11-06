#include "pch.h"
#include "BansheeScream.h"
#include "Entity.h"

BansheeScream::BansheeScream(const Point2f& pivot, int damage)
	: Weapon(damage)
{
	Setup(pivot);
}

BansheeScream::~BansheeScream()
{
	for (Sprite* pSprite : m_pSpriteVec)
		delete pSprite;
}

void BansheeScream::Setup(const Point2f& pivot)
{
	const std::string id{ "bansheeScream" };
	m_pTexture = GetTextureManager().GetTexture(id);

	const float sizeRatio{ 1.5f };
	m_MinScale = GetTextureManager().GetScale(id);
	m_MaxScale = m_MinScale * sizeRatio;

	const int nrScreamSprites{ 3 };
	for (int index{}; index < nrScreamSprites; ++index)
	{
		const float opacity{ 1 - 1.f / index };
		const float scale{ m_MinScale + (m_MaxScale - m_MinScale) / nrScreamSprites * index };
		m_pSpriteVec.push_back(CreateScreamSprite(pivot, scale));
		m_OpacityVec.push_back(opacity);
	}
}

Sprite* BansheeScream::CreateScreamSprite(const Point2f& pivot, float scale)
{
	const float width{ m_pTexture->GetWidth() };
	const Point2f bottomLeft{ pivot.x - width / 2, pivot.y };

	return new BasicSprite{ m_pTexture, bottomLeft, scale };
}

void BansheeScream::Draw() const
{
	Weapon::Draw();
	for (int index{}; index < m_pSpriteVec.size(); ++index)
	{
		glColor4f(1, 1, 1, m_OpacityVec[index]);
		m_pSpriteVec[index]->Draw();
	}
	glColor4f(1, 1, 1, 1);
}

void BansheeScream::Update(Entity* pOwner, float deltaTime)
{
	const float scaleRate{ 1.5f };
	SetHitBox(pOwner->GetPivot());
	GetPlayer()->Hurt(m_Hitbox, m_Damage);

	for (int index{}; index < m_pSpriteVec.size(); ++index)
	{
		BasicSprite* pSimpleSprite{ dynamic_cast<BasicSprite*>(m_pSpriteVec[index]) };
		const float scale{ pSimpleSprite->GetScale() + scaleRate * deltaTime };
		pSimpleSprite->SetScale((scale < m_MaxScale) ? scale : m_MinScale);
		pSimpleSprite->SetPivot(pOwner->GetPivot());

		m_OpacityVec[index] = 1 - (scale / m_MaxScale);
	}
}

void BansheeScream::SetHitBox(const Point2f& pivot)
{
	const float width{ m_pTexture->GetWidth() * m_MaxScale };
	const float height{ m_pTexture->GetHeight() * m_MaxScale };
	m_Hitbox = Rectf{ pivot.x - width / 2, pivot.y, width, height };
}