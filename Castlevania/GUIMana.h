#pragma once
#include "GUIStat.h"
class BasicSprite;

class GUIMana : public  GUIStat
{
public:
	GUIMana(BasicSprite* pSprite);
	virtual ~GUIMana() override;

	GUIMana(const GUIMana& other) = delete;
	GUIMana& operator=(const GUIMana& other) = delete;
	GUIMana(GUIMana&& other) noexcept = delete;
	GUIMana& operator=(GUIMana&& other) noexcept = delete;

	virtual void Draw() const override;
	virtual void Update(int stat, float deltaTime) override;

private:
	void UpdateOpacity(float deltaTime);

	BasicSprite* m_pSprite{ nullptr };
	float m_Opacity{ 0 };
	float m_Timer{};
};