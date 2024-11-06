#pragma once
#include "BasicSprite.h"
class Texture;

class TextSprite : public BasicSprite
{
public:
	TextSprite(const std::string& text, const std::string& fontPath, int fontSize = 16, const Color4f& color = Color4f{ 0, 0, 0, 1 });
	virtual ~TextSprite() override;

	TextSprite(const TextSprite& other) = delete;
	TextSprite& operator=(const TextSprite& other) = delete;
	TextSprite(TextSprite&& other) noexcept = delete;
	TextSprite& operator=(TextSprite&& other) noexcept = delete;

	void Update(float elapsedSec) override {}

	void SetText(const std::string& text);
	void SetFontSize(int fontSize);
	void SetColor(const Color4f& color);

private:
	void UpdateTexture();

	std::string m_Text{};
	const std::string m_FontPath{};
	int m_FontSize{};
	Color4f m_Color{};
};