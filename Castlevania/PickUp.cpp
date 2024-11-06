#include "pch.h"
#include "debugPch.h"
#include "PickUp.h"
#include "Player.h"
#include "utils.h"

PickUp::~PickUp()
{
	delete m_pSprite;
}

void PickUp::Draw() const
{
	m_pSprite->Draw();
#ifdef _DEBUG_OBJECTS
	const Color4f pickUpColor{ 0,0,1,1 };
	utils::SetColor(pickUpColor);
	utils::DrawRect(m_RigidBody.GetHurtBox());
#endif
}

void PickUp::Update(float deltaTime)
{
	UpdateRigidBody(deltaTime);
}

void PickUp::UpdateRigidBody(float deltaTime)
{
	m_RigidBody.UpdatePhysics(deltaTime);
	m_RigidBody.CollideHard();
	m_RigidBody.CollideSoft();
}

void PickUp::SetSprite(Sprite* pSprite)
{
	m_pSprite = pSprite;
}

bool PickUp::Collect()
{
	return utils::IsOverlapping(m_RigidBody.GetHurtBox(), GetPlayer()->GetHurtBox());
}
