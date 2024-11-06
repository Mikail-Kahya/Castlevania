#pragma once
#include "GUIStat.h"

class GUICounter : public  GUIStat
{
public:
	GUICounter(const Point2f& pivot);
	virtual ~GUICounter() override;

	GUICounter(const GUICounter& other) = delete;
	GUICounter& operator=(const GUICounter& other) = delete;
	GUICounter(GUICounter&& other) noexcept = delete;
	GUICounter& operator=(GUICounter&& other) noexcept = delete;

	void Draw() const override;
	void Update(int stat, float deltaTime) override;

private:
	TextSprite* m_pSprite{ nullptr };
};