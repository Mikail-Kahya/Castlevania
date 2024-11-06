#include "pch.h"
#include "Confodore.h"

Confodore::Confodore(const std::string& hand)
	: PlayerWeapon(7)
{
	Setup(hand);
}

void Confodore::Setup(const std::string& hand)
{
	BasicSprite* pSprite{ dynamic_cast<BasicSprite*>(GetTextureManager().CreateSprite("confodore"))};
	m_Hitbox = Rectf{ 0, 0, pSprite->GetWidth(), pSprite->GetHeight() };
	
	SetSprite(pSprite);

	if (hand == "left")
	{
		SetOffset(Point2f{ 30, 45 }, State::standing);
		SetOffset(Point2f{ 40, 20 }, State::crouched);
		SetOffset(Point2f{ 40, 48 }, State::air);
	}
	else if (hand == "right")
	{
		SetOffset(Point2f{ 25, 42 }, State::standing);
		SetOffset(Point2f{ 25, 18 }, State::crouched);
		SetOffset(Point2f{ 25, 42 }, State::air);
	}
}