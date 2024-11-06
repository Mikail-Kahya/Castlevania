#pragma once
#include "GUIStat.h"

class GUIBar : public  GUIStat
{
public:
	GUIBar(BasicSprite* pSprite, const Rectf& fullSrcRect);
	virtual ~GUIBar() override;

	GUIBar(const GUIBar& other) = delete;
	GUIBar& operator=(const GUIBar& other) = delete;
	GUIBar(GUIBar&& other) noexcept = delete;
	GUIBar& operator=(GUIBar&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update(int stat, float deltaTime) override;

private:
	BasicSprite* m_pSprite{ nullptr };
	const Rectf m_FullSrcRect{};
};

