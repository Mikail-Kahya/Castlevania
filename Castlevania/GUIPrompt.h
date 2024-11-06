#pragma once
#include "GUIElement.h"

class GUIPrompt : public  GUIElement
{
public:
	GUIPrompt(const std::string& prompt, const Point2f& pivot);
	virtual ~GUIPrompt() override;

	GUIPrompt(const GUIPrompt& other) = delete;
	GUIPrompt& operator=(const GUIPrompt& other) = delete;
	GUIPrompt(GUIPrompt&& other) noexcept = delete;
	GUIPrompt& operator=(GUIPrompt&& other) noexcept = delete;

	void Draw() const override;
	void Update(float deltaTime) override {}

private:
	TextSprite* m_pSprite{ nullptr };
	Rectf m_Background{};
};