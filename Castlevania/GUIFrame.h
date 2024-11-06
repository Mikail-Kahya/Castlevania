#pragma once
#include "GUIElement.h"

class GUIFrame : public GUIElement
{
public:
	GUIFrame(Sprite* pSprite, float opacity = 1);
	virtual ~GUIFrame() override;

	GUIFrame(const GUIFrame& other) = delete;
	GUIFrame& operator=(const GUIFrame& other) = delete;
	GUIFrame(GUIFrame&& other) noexcept = delete;
	GUIFrame& operator=(GUIFrame&& other) noexcept = delete;

	virtual void Draw() const;
	virtual void Update(float deltaTime) override {};

	float GetOpacity() const;

private:
	Sprite* m_pSprite{ nullptr };
	float m_Opacity{};
};

