#include "pch.h"
#include "debugPch.h"
#include "Magnet.h"
#include "Player.h"
#include "InAirState.h"

Magnet::Magnet(const Point2f& bottomLeft)
{
	Setup(bottomLeft);
}

Magnet::~Magnet()
{
	delete m_pMagnetSprite;
	delete m_pActiveSprite;
}

void Magnet::Setup(const Point2f& bottomLeft)
{
	m_pMagnetSprite = GetTextureManager().CreateSprite("magnet");
	m_pActiveSprite = GetTextureManager().CreateSprite("magnetEffect");

	const float magnetHalfHeight{ m_pMagnetSprite->GetHeight() / 2 };
	m_Center = Point2f{ bottomLeft.x + m_pMagnetSprite->GetWidth() / 2,
						bottomLeft.y + magnetHalfHeight };
	m_pMagnetSprite->SetPivot(Point2f{ m_Center.x, m_Center.y - magnetHalfHeight });
	m_pActiveSprite->SetPivot(Point2f{ m_Center.x, m_Center.y - m_pActiveSprite->GetHeight() / 2 });
}

void Magnet::Update(float deltaTime)
{
	m_pMagnetSprite->Update(deltaTime);
	ActivateMagnet();
	UpdateAttractionPoint();
	if (m_IsActive)
	{
		Attract(deltaTime);
		PulseActiveEffect(deltaTime);
	}
	else if (!m_IsActive)
	{
		Repel();
	}
	LockPlayerControls(deltaTime);
}

void Magnet::Draw() const
{
	if (m_IsActive)
	{
		glColor4f(1, 1, 1, m_ActiveOpacity);
		m_pActiveSprite->Draw();
		glColor4f(1, 1, 1, 1);
	}

	m_pMagnetSprite->Draw();

#ifdef _DEBUG_COLLISION
	glColor4f(0, 0, 1, 1);
	const float attractRadius{ GetAttractRadius() };
	utils::DrawEllipse(m_Center, attractRadius, attractRadius);
	glColor4f(1, 1, 1, 1);
#endif
}

void Magnet::ActivateMagnet()
{
	m_IsActive = false;
	m_AttractTimer = 0;
	const Uint8* pKeyStates{ SDL_GetKeyboardState(nullptr) };
	if (pKeyStates[SDL_SCANCODE_LSHIFT])
	{
		const Point2f from{ m_Center };
		const Point2f to{ GetPlayerCenter() };
		const Vector2f distance{ from, to };
		const float attractRadius{ GetAttractRadius() };

		if (distance.Length() < attractRadius)
		{

			if (!m_IsActive)
				SetPlayerState(new FallingState{ GetPlayer() });

			if (!m_IsActive && !m_IsRepelling)
			{
				GetSoundManager().StopEffects();
				GetSoundManager().PlaySound("MagnetActivate");
			}
				
			m_IsActive = true;
		}
	}
}

void Magnet::PulseActiveEffect(float deltaTime)
{
	if(m_OpacityRise)
	{
		m_OpacityTimer += deltaTime;
		m_OpacityRise = m_OpacityTimer < 1;
	}
	else
	{
		m_OpacityTimer -= deltaTime;
		m_OpacityRise = m_OpacityTimer < 0;
	}
	
	const float min{ 0.4f }, max{ 0.8f };
	m_ActiveOpacity = (1 - m_OpacityTimer) * min + m_OpacityTimer * max;
}

void Magnet::Attract(float deltaTime)
{
	m_AttractTimer += deltaTime;
	const Point2f playerCenter{ GetPlayerCenter() };

	Point2f pivot{	(1 - m_AttractTimer) * playerCenter.x + m_AttractTimer * m_AttractionPoint.x,
					(1 - m_AttractTimer) * playerCenter.y + m_AttractTimer * m_AttractionPoint.y };
	pivot.y -= GetPlayer()->GetHurtBox().height / 2;

	if (!IsPlayerCollidingHard())
		SetPlayerPivot(pivot);
	
	SetPlayerVelocity(Vector2f{});
}

void Magnet::Repel()
{
	if (!m_IsRepelling) return;

	const Vector2f playerToCenter{ GetPlayerCenter(), m_Center };
	const float launchScalar{ 9 };
	SetPlayerVelocity(playerToCenter * launchScalar);
	m_IsRepelling = false;
	m_IsRepelled = true;
}

void Magnet::UpdateAttractionPoint()
{
	// reset mouse and attraction point if magnet is not activated
	if (!m_IsActive && !m_IsRepelling)
	{
		m_AttractionPoint = m_Center;
		m_LaunchVelocity = Vector2f{};
		return;
	}

	int sdlX{ }, sdlY{ };
	SDL_GetRelativeMouseState(&sdlX, &sdlY);
	m_LaunchVelocity.x += sdlX;
	m_LaunchVelocity.y -= sdlY;

	// put a hard limit on attraction translate
	const float margin{ 10 };
	const float attractRadius{ GetAttractRadius() - margin };
	if (m_LaunchVelocity.Length() > attractRadius)
		m_LaunchVelocity = m_LaunchVelocity.Normalized() * attractRadius;

	m_AttractionPoint = m_Center + m_LaunchVelocity;
	m_IsRepelling = true;
}

void Magnet::LockPlayerControls(float deltaTime)
{
	if (m_IsActive)
	{
		SetPlayerAvoidPlatforms(true);
		GetPlayer()->AllowControl(false);
		return;
	}

	if(m_IsRepelled)
	{
		const bool isGrounded{ GetPlayer()->IsGrounded() };
		GetPlayer()->AllowControl(isGrounded);
		m_IsRepelled = !isGrounded;
	}
}

Point2f Magnet::GetPlayerCenter() const
{
	const Point2f pivot{ GetPlayer()->GetPivot() };
	return Point2f{ pivot.x, pivot.y + GetPlayer()->GetHurtBox().height / 2 };
}

float Magnet::GetAttractRadius() const
{
	return m_pActiveSprite->GetWidth() / 2;
}