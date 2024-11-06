#include "pch.h"
#include "TriggerBox.h"
#include "utils.h"

TriggerBox::TriggerBox()
	: TriggerBox(Rectf{})
{
}

TriggerBox::TriggerBox(const Rectf& triggerBox, bool triggerOnce)
	: m_TriggerBox{ triggerBox }
	, m_TriggerOnce{ triggerOnce }
{
}

void TriggerBox::Update()
{
	if (m_TriggerOnce && m_Triggered) return;
	m_Triggered = utils::IsOverlapping(GetPlayer()->GetHurtBox(), m_TriggerBox);
}

bool TriggerBox::IsTriggered() const
{
	return m_Triggered;
}

Point2f TriggerBox::GetPivot() const
{
	return Point2f{ m_TriggerBox.left + m_TriggerBox.width / 2, m_TriggerBox.bottom };
}
