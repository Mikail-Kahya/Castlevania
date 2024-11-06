#include "pch.h"
#include "debugPch.h"
#include "Destructable.h"
#include "utils.h"

Destructable::~Destructable()
{
	delete m_pSprite;
}

void Destructable::Update(float deltaTime)
{
	m_pSprite->Update(deltaTime);
}

void Destructable::Draw() const
{
	m_pSprite->Draw();
#ifdef _DEBUG_OBJECTS
		utils::SetColor(Color4f{ 1, 1, 0 , 1 });
		utils::DrawRect(m_HurtBox);
#endif
}

bool Destructable::AllowDelete() const
{
	return m_AllowDelete;
}

bool Destructable::Hurt(const Rectf& hitBox)
{
	if ( m_AllowDelete || m_Hit) return false;

	if(utils::IsOverlapping(hitBox, m_HurtBox))
		return m_Hit = true;

	return false;
}

void Destructable::SetRigidPivot(const Point2f& pivot)
{
	m_HurtBox.left = pivot.x - m_HurtBox.width / 2;
	m_HurtBox.bottom = pivot.y;
}

void Destructable::SetDelete(bool canDelete)
{
	m_AllowDelete = canDelete;
}