#pragma once
#include "GUIElement.h"

class GUIStat : public GUIElement
{
public:
	GUIStat();
	GUIStat(int maxStat, int currentStat);
	virtual ~GUIStat() = default;

	GUIStat(const GUIStat& other) = delete;
	GUIStat& operator=(const GUIStat& other) = delete;
	GUIStat(GUIStat&& other) noexcept = delete;
	GUIStat& operator=(GUIStat&& other) noexcept = delete;

	virtual void Draw() const = 0;
	virtual void Update(int stat, float deltaTime) = 0;

	void SetMaxStat(int maxStat);

protected:
	void SetCurrentStat(int currentStat);
	float GetRatio() const;
	bool IsChanged() const;

private:
	virtual void Update(float deltaTime) override {};

	int m_MaxStat{};
	int m_CurrentStat{};
	bool m_StatChanged{ false };
};