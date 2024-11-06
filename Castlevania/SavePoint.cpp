#include "pch.h"
#include "SavePoint.h"
#include "Game.h"
#include "OrbPart.h"
#include "RisingSparkle.h"
#include "GUIPrompt.h"

SavePoint::SavePoint(const Point2f& bottomLeft)
{
	Setup(bottomLeft);
	SpawnSparkles();
}

SavePoint::~SavePoint()
{
	delete m_pStatue;
	delete m_pOrb;
	delete m_pButtonPrompt;

	for (Particle* pSparkle : m_pSparkleVec)
		delete pSparkle;
}

void SavePoint::Update(float deltaTime)
{
	if (Level::RoomChanged())
		Reset();

	UpdateSparkles(deltaTime);
	switch (m_State)
	{
	case State::unsaved:
		UpdateUnsaved(deltaTime);
		break;
	case State::isSaving: 
		UpdateSaving(deltaTime);
		break;
	}
}

void SavePoint::Draw() const
{
	m_pOrb->Draw();
	DrawSaving();
	m_pStatue->Draw();
	DrawParticles();
	DrawPrompt();
}

void SavePoint::Setup(const Point2f& bottomLeft)
{
	m_pStatue = GetTextureManager().CreateSprite("statue", bottomLeft);
	m_pOrb = dynamic_cast<Avatar*>(GetTextureManager().CreateSprite("orb", bottomLeft));
	m_pOrb->SetActiveAnimation("unsaved");

	const float height{ m_pStatue->GetHeight() }, width{ m_pStatue->GetWidth() };
	const float heightOffset{ 0.7f };
	const float widthOffset{ 0.5f };

	Point2f orbPivot{ bottomLeft };
	orbPivot.x += width * widthOffset;
	orbPivot.y += height * heightOffset;
	m_pOrb->SetPivot(orbPivot);

	m_TriggerBox = TriggerBox{ Rectf{ bottomLeft, width, height }, false };

	m_pButtonPrompt = new GUIPrompt{ "F to save", orbPivot };

}

void SavePoint::Reset()
{
	m_AudioActive = false;
	m_State = State::unsaved;
	m_pOrb->SetActiveAnimation("unsaved");
	m_SavingGlow = 0;
}

void SavePoint::UpdateUnsaved(float deltaTime)
{
	if (!m_AudioActive)
	{
		GetSoundManager().PlaySound("SavePointUnsaved");
		m_AudioActive = true;
	}
		

	m_pOrb->Update(deltaTime);
	const Uint8* pKeyStates{ SDL_GetKeyboardState(nullptr) };
	m_TriggerBox.Update();
	if (m_TriggerBox.IsTriggered() && pKeyStates[SDL_SCANCODE_F] && m_State == State::unsaved)
	{
		m_State = State::isSaving;
		Game::SaveGame(Point2f{ m_TriggerBox.GetPivot() });
		GetSoundManager().StopEffects();
		GetSoundManager().PlaySound("SavePointSave");
	}

	DeleteSparkles();
	SpawnSparkles();
}

void SavePoint::UpdateSaving(float deltaTime)
{
	m_pOrb->Update(deltaTime);

	const float glowRate{ 1.5f };
	m_SavingGlow += deltaTime * glowRate;

	if (m_SavingGlow > 1)
	{
		m_pOrb->SetActiveAnimation("saved");
		m_State = State::saved;
		BreakOrb();
	}
}

void SavePoint::UpdateSparkles(float deltaTime)
{
	for (Particle* pSparkle : m_pSparkleVec)
		if (pSparkle)
			pSparkle->Update(deltaTime);
}

void SavePoint::DeleteSparkles()
{
	for (Particle*& pSparkle : m_pSparkleVec)
	{
		if (!pSparkle) continue;
		if (pSparkle->AllowDelete())
		{
			delete pSparkle;
			pSparkle = nullptr;
		}
	}
}

void SavePoint::SpawnSparkles()
{
	for (Particle*& pSparkle : m_pSparkleVec)
	{
		if (pSparkle) continue;
		const float width{ m_pStatue->GetWidth() }, height{ m_pStatue->GetHeight() / 2 };

		Point2f bottomLeft{ m_pStatue->GetPosition() };
		bottomLeft.y += height;

		pSparkle = new RisingSparkle{ myUtils::GetRandPointInRect(Rectf{bottomLeft, width, height}), true };
	}
}

void SavePoint::DrawPrompt() const
{
	if (m_TriggerBox.IsTriggered() && m_State == State::unsaved)
		m_pButtonPrompt->Draw();
}

void SavePoint::DrawSaving() const
{
	if (m_State != State::isSaving) return;

	const float radius{ m_pOrb->GetWidth() / 2 };
	Point2f center{ m_pOrb->GetPosition() };

	center.x += radius;
	center.y += radius;

	glColor4f(1, 1, 1, m_SavingGlow);
	utils::FillEllipse(center, radius, radius);
	glColor4f(1, 1, 1, 1);
}

void SavePoint::DrawParticles() const
{
	for (Particle* pSparkle : m_pSparkleVec)
		if (pSparkle)
			pSparkle->Draw();
}

void SavePoint::BreakOrb()
{
	const size_t nrParts{ OrbPart::GetNrParts() };
	for (int index{}; index < nrParts; ++index)
		GetParticleManager().AddParticle(new OrbPart{ m_pOrb->GetPosition(), index });
	GetSoundManager().PlaySound("SavePointSaved");
}
