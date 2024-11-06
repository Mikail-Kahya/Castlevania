#include "pch.h"
#include "Sparkle.h"
#include "myUtils.h"

Sparkle::Sparkle(const Point2f& center, bool isBlue, float maxTime, int index)
	: m_ParticleTime{ myUtils::GenRand(maxTime) }
	, m_ParticleTimer{ m_ParticleTime }
{
	SetupSprite(center, isBlue, index);
}

Sparkle::~Sparkle()
{
	delete m_pSprite;
}

void Sparkle::SetupSprite(const Point2f& center, bool isBlue, int index)
{
	std::string id{ "sparkle" };
	if (isBlue)
		id += "Blue";
	else
		id += "Red";
		
	Anim animation{ GetTextureManager().GetAnimation(id, 0) };
	if (index < 0)
		index = myUtils::GenRand(animation.nrFrames);

	const int col{ index % animation.cols };
	const int row{ index / animation.cols + 1 };
	const Rectf srcRect{ col * animation.frameWidth, row * animation.frameHeight,
							animation.frameWidth, animation.frameHeight };

	m_pSprite = new BasicSprite{ GetTextureManager().GetTexture(id), Point2f{}, GetTextureManager().GetScale(id) };
	m_pSprite->SetSrcRect(srcRect);
	m_pSprite->SetCenter(center);
}

void Sparkle::Update(float deltaTime)
{
	m_ParticleTimer -= deltaTime;
	if (m_ParticleTimer < 0)
		m_Delete = true;
}

void Sparkle::Draw() const
{
	glColor4f(1, 1, 1, GetOpacity());
	m_pSprite->Draw();
	glColor4f(1, 1, 1, 1);
}

void Sparkle::SetCenter(const Point2f& center)
{
	m_pSprite->SetCenter(center);
}

float Sparkle::GetOpacity() const
{
	return m_ParticleTimer / m_ParticleTime;
}
