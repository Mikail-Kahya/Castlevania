#pragma once
#include "MapMechanic.h"
#include "TriggerBox.h"
class GUIPrompt;

class SavePoint : public MapMechanic
{
public:
	SavePoint(const Point2f& bottomLeft);
	virtual ~SavePoint() override;

	SavePoint(const SavePoint& other) = delete;
	SavePoint& operator=(const SavePoint& other) = delete;
	SavePoint(SavePoint&& other) noexcept = delete;
	SavePoint& operator=(SavePoint&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;
	static bool IsSaving();

private:
	void Setup(const Point2f& bottomLeft);
	void Reset();

	void UpdateUnsaved(float deltaTime);
	void UpdateSaving(float deltaTime);
	void UpdateSparkles(float deltaTime);
	void DeleteSparkles();
	void SpawnSparkles();

	void DrawPrompt() const;
	void DrawSaving() const;
	void DrawParticles() const;

	void BreakOrb();

	enum class State { unsaved, isSaving, saved };

	GUIPrompt* m_pButtonPrompt{};
	Sprite* m_pStatue{};
	Avatar* m_pOrb{};
	TriggerBox m_TriggerBox{};
	State m_State{ State::unsaved };
	float m_SavingGlow{};
	bool m_AudioActive{ false };

	std::vector<Particle*> m_pSparkleVec{ 20 };
};
