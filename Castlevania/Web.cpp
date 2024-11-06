#include "pch.h"
#include "Web.h"

Web::Web(const Point2f& from, const Point2f& to)
	: ThrowableWeapon(18, from, to, 1)
{
	m_pSprite = dynamic_cast<Avatar*>(GetTextureManager().CreateSprite("arthrovertaWeb"));
	m_pSprite->SetActiveAnimation("up");
}

Web::~Web()
{
	delete m_pSprite;
}

void Web::Draw() const
{
	ThrowableWeapon::Draw();
	glColor4f(1, 1, 1, m_Opacity);
	m_pSprite->Draw();
	glColor4f(1, 1, 1, 1);
}

void Web::Update(Entity* pOwner, float deltaTime)
{
	ThrowableWeapon::Update(pOwner, deltaTime);
	m_IsFading = (m_IsFading) ? m_IsFading : m_RigidBody.IsGrounded();
	if (m_IsFading)
	{
		FadeOut(deltaTime);
		return;
	}

	m_pSprite->Update(deltaTime);

	const float hitBoxRatio{ 0.8f };
	m_RigidBody.SetWidth(m_pSprite->GetWidth() * hitBoxRatio);
	m_RigidBody.SetHeight(m_pSprite->GetHeight() * hitBoxRatio);
	m_Hitbox = m_RigidBody.GetHurtBox();

	m_pSprite->SetPivot(m_RigidBody.GetPivot());
	const float angle{ m_RigidBody.GetVelocity().Angle() * 180 / float(M_PI) };
	m_pSprite->SetRotation(angle);

	ChangeAnimation();
}

void Web::OnHit()
{
	m_IsFading = true;
}

void Web::ChangeAnimation()
{
	const float unfoldSpeed{ 50 };
	if (!m_IsOpen && abs(m_RigidBody.GetVelocity().y) < unfoldSpeed)
	{
		m_pSprite->SetActiveAnimation("open");
		m_IsOpen = true;
	}

	if (m_IsOpen && m_pSprite->IsLastFrame())
		m_pSprite->SetActiveAnimation("fall");
}

void Web::FadeOut(float deltaTime)
{
	const float fadeRate{ 3 };
	m_Opacity -= fadeRate * deltaTime;
	if (m_Opacity < 0)
		m_AllowDelete = true;
}
