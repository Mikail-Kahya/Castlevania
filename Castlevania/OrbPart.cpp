#include "pch.h"
#include "OrbPart.h"
#include "myUtils.h"

std::vector<Part> OrbPart::m_PartVec{};

OrbPart::OrbPart(const Point2f& bottomLeft, int partIndex)
	: FlyingParticle(bottomLeft, Vector2f{})
{
	LoadStatics();

	m_Velocity = m_PartVec[partIndex].velocity;

	const std::string id{ "orb" };
	Texture* pTexture{ GetTextureManager().GetTexture(id) };
	const float scale{ GetTextureManager().GetScale(id) };

	m_pSprite = new BasicSprite{ pTexture, bottomLeft, scale };
	m_pSprite->SetSrcRect(m_PartVec[partIndex].srcRect);
}

void OrbPart::LoadStatics()
{
	if (!m_PartVec.empty()) return;
	m_PartVec = myUtils::CreateParts("./MapMechanic/SavePoint/OrbBreak.json");
}

void OrbPart::Update(float deltaTime)
{
	FlyingParticle::Update(deltaTime);
	const int opacityRate{ 2 };
	m_Opacity -= opacityRate * deltaTime;
	m_Delete = m_Opacity > 1;
	m_pSprite->SetPosition(m_BottomLeft);
}

void OrbPart::Draw() const
{
	glColor4f(1, 1, 1, m_Opacity);
	m_pSprite->Draw();
	glColor4f(1, 1, 1, 1);
}

size_t OrbPart::GetNrParts()
{
	LoadStatics();
	return m_PartVec.size();
}
