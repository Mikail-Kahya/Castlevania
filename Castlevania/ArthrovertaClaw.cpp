#include "pch.h"
#include "ArthrovertaClaw.h"
#include "Dust.h"
#include "Entity.h"

ArthrovertaClaw::ArthrovertaClaw(const Point2f& pivot, int damage)
	: Weapon(damage)
{
	SetupHitBox(pivot);
}

ArthrovertaClaw::~ArthrovertaClaw()
{
	delete m_pSprite;
}

void ArthrovertaClaw::Draw() const
{
	m_pSprite->Draw();
	Weapon::Draw();
}

void ArthrovertaClaw::Update(Entity* pOwner, float deltaTime)
{
	Weapon::Update(pOwner, deltaTime);
	if (m_IsActive)
	{
		const Point2f& pivot{ pOwner->GetPivot() };
		if (m_AttackState == State::sendOut)
			m_Start = Vector2f{ pivot };

		UpdateHitBox(pivot, deltaTime);
		GetPlayer()->Hurt(m_Hitbox, m_Damage);

		UpdateSprites(pivot, deltaTime);
		m_pSprite->SetPivot(pivot + m_ShoulderOffset);
	}
}

bool ArthrovertaClaw::Use(float delay)
{
	if (Weapon::Use(delay))
	{
		SendOutClaw();
		return true;
	}
	return false;
}

void ArthrovertaClaw::UpdateSprites(const Point2f& pivot, float deltaTime)
{
	m_pSprite->Update(deltaTime);

	AnimatedSprite* pAnimatedSprite{ dynamic_cast<AnimatedSprite*>(m_pSprite) };

	switch (m_AttackState)
	{
	case State::sendOut: 
		if (pAnimatedSprite->IsLastFrame())
			SwingClaw();
		break;
	case State::swing:
		UpdateSwing(pivot);
		if (m_StateTimer > m_LerpTime)
			RetractClaw();
		break;
	case State::retract:
		if (pAnimatedSprite->IsLastFrame())
			m_IsActive = false;
		break;
	}
}

void ArthrovertaClaw::SendOutClaw()
{
	delete m_pSprite;
	m_pSprite = GetTextureManager().CreateSprite("arthrovertaClaw");
	m_pSprite->SetRotatePivot(true);
	m_pSprite->SetRotation(90);

	m_ShoulderOffset = m_BaseShoulderOffset;
	m_AttackState = State::sendOut;
	Reset(dynamic_cast<AnimatedSprite*>(m_pSprite)->GetAnimationTime());
}

void ArthrovertaClaw::SwingClaw()
{
	const float animatedHeight{ m_pSprite->GetHeight() };

	delete m_pSprite;
	m_pSprite = GetTextureManager().CreateSprite("arthrovertaClawActive");
	m_pSprite->SetRotatePivot(true);

	const float deltaHeight{ (animatedHeight - m_pSprite->GetHeight()) / 2 };

	m_ShoulderOffset.x -= deltaHeight;
	m_AttackState = State::swing;
	Reset(0.3f);
}

void ArthrovertaClaw::RetractClaw()
{
	const float angle{ m_pSprite->GetRotation() };
	delete m_pSprite;

	m_pSprite = GetTextureManager().CreateSprite("arthrovertaClaw");
	m_pSprite->SetRotatePivot(true);
	m_pSprite->SetRotation(angle);
	dynamic_cast<AnimatedSprite*>(m_pSprite)->FullReverse();

	m_AttackState = State::retract;
	m_ShoulderOffset = m_BaseShoulderOffset;
	m_ShoulderOffset.y += 30;
	Reset(dynamic_cast<AnimatedSprite*>(m_pSprite)->GetAnimationTime());

	GetParticleManager().AddParticle(new Dust{ GetPivot(), 2.5f });
}

void ArthrovertaClaw::Reset(float lerpTime)
{
	m_LerpTime = lerpTime;
	m_StateTimer = 0;
	m_Start = Vector2f{ GetPivot() };
}

void ArthrovertaClaw::SetupHitBox(const Point2f& pivot)
{
	const Vector2f hitboxOffset{ -220, 150 };
	const float width{ 100 }, height{ 50 };

	m_Hitbox = Rectf{ pivot + hitboxOffset, width, height };
	m_StartHeight = m_Hitbox.bottom - pivot.y;
	m_Start = Vector2f{ m_Hitbox.left + m_Hitbox.width / 2, m_Hitbox.bottom };
}

void ArthrovertaClaw::UpdateSwing(const Point2f& pivot)
{
	const Point2f hitBoxCenter{	m_Hitbox.left + m_Hitbox.width / 2,
								m_Hitbox.bottom + m_Hitbox.height / 2 };

	const float startAngle{ 45 };
	const float angle{ Vector2f(pivot, hitBoxCenter).Angle() * 180 / float(M_PI) - startAngle };
	m_pSprite->SetRotation(angle);
}

void ArthrovertaClaw::UpdateHitBox(const Point2f& pivot, float deltaTime)
{
	m_StateTimer += deltaTime;
	const float time{ m_StateTimer / m_LerpTime };

	const int nrStates{ int(State::retract) + 1 };
	const Vector2f offsetArr[nrStates]
	{
		Vector2f { -220, 150 },
		Vector2f { -180, 0 },
		Vector2f { 0, 0 },
	};

	const Vector2f end{ pivot + offsetArr[int(m_AttackState)] };
	const Point2f position{ (1 - time) * m_Start + time * end};
	SetPivot(position);
}

void ArthrovertaClaw::SetPivot(const Point2f& pivot)
{
	const Point2f bottomLeft{ pivot.x - m_Hitbox.width / 2, pivot.y };
	m_Hitbox = bottomLeft;
}

Point2f ArthrovertaClaw::GetPivot() const
{
	return Point2f{ m_Hitbox.left + m_Hitbox.width / 2, m_Hitbox.bottom };
}
