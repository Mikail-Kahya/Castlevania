#pragma once
#include "myStructs.h"
#include "Avatar.h"
#include "BasicSprite.h"
#include "TextSprite.h"
#include "Texture.h"

using Animations = std::map<std::string, Anim>;

class TextureManager final
{
public:
	friend TextureManager& GetTextureManager();

	~TextureManager();

	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator=(const TextureManager& other) = delete;
	TextureManager(TextureManager&& other) noexcept = delete;
	TextureManager& operator=(TextureManager&& other) noexcept = delete;

	Anim GetAnimation(const std::string& id, int index) const;
	Texture* GetTexture(const std::string& id);
	float GetScale(const std::string& id);
	Sprite* CreateSprite(const std::string& id, const Point2f& bottomLeft = Point2f{ 0,0 });
	TextSprite* CreateText(const std::string& text, const Point2f& pivot = Point2f{}, int fontSize = 16, const Color4f & color = Color4f{ 1,1,1,1 });
	TextSprite* CreateText(int number, const Point2f& pivot = Point2f{}, int fontSize = 16, const Color4f& color = Color4f{ 1,1,1,1 });

private:
	TextureManager();

	void Setup();
	void LoadTexture(const std::string& id, const nlohmann::json& data);
	void LoadAnimations(const std::string& id, const nlohmann::json& data);

	std::map<std::string, Texture*> m_pTextureMap{};
	std::map<std::string, Animations> m_AnimationsMap{};
	std::map<std::string, float> m_ScaleMap{};
};

inline TextureManager& GetTextureManager()
{
	static TextureManager textureManager{};
	return textureManager;
}