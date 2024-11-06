#include "pch.h"
#include "TextureManager.h"
#include "myUtils.h"

TextureManager::TextureManager()
{
	Setup();
}

TextureManager::~TextureManager()
{
	for (const auto& texturePair : m_pTextureMap)
		delete texturePair.second;
}

void TextureManager::Setup()
{
	if (!m_pTextureMap.empty()) return;

	nlohmann::json data{};
	myUtils::ParseJson("./Manager/TextureManager.json", data);

	for (const nlohmann::json& textureData : data)
	{
		const std::string id{ textureData["id"] };

		LoadTexture(id, textureData);

		const float scale = (textureData.contains("scale")) ? float(textureData["scale"]) : 1;
		m_ScaleMap.insert({ id, scale });

		if (textureData.contains("animations"))
			LoadAnimations(id, textureData["animations"]);
	}
}

void TextureManager::LoadTexture(const std::string& id, const nlohmann::json& data)
{
	m_pTextureMap.insert({ id, new Texture{data["path"]} });
}

void TextureManager::LoadAnimations(const std::string& id, const nlohmann::json& data)
{
	Animations animations{};
	for (const nlohmann::json& animationData : data)
		animations.insert({ animationData["id"], myUtils::CreateAnim(animationData) });
	m_AnimationsMap.insert({ id, animations });
}

Anim TextureManager::GetAnimation(const std::string& id, int index) const
{
	auto anims{ m_AnimationsMap.find(id) };
	int indexCounter{};
	for (const auto& animPair: anims->second)
	{
		if (indexCounter == index)
			return animPair.second;

		++indexCounter;
	}
	return Anim{};
}

Texture* TextureManager::GetTexture(const std::string& id)
{
	auto pTextureIterator{ m_pTextureMap.find(id) };
	return (pTextureIterator != m_pTextureMap.end()) ? pTextureIterator->second : nullptr;
}

float TextureManager::GetScale(const std::string& id)
{
	auto scaleIterator{ m_ScaleMap.find(id) };
	return (scaleIterator != m_ScaleMap.end()) ? scaleIterator->second : 1;
}

Sprite* TextureManager::CreateSprite(const std::string& id, const Point2f& bottomLeft)
{
	const float scale{ m_ScaleMap[id] };
	const Texture* pTexture{ m_pTextureMap[id] };
	const auto animationsIterator{ m_AnimationsMap.find(id) };

	if (animationsIterator == m_AnimationsMap.end())
	{
		return new BasicSprite{ pTexture, bottomLeft, scale };
	}
		
	if (animationsIterator->second.size() == 1)
	{
		AnimatedSprite* pAnimatedSprite{ new AnimatedSprite{ pTexture, bottomLeft, scale } };
		pAnimatedSprite->SetAnimation(animationsIterator->second.begin()->second);
		return pAnimatedSprite;
	}
		
	if(animationsIterator->second.size() > 1)
	{
		Avatar* pAvatar{ new Avatar{ pTexture, bottomLeft, scale } };
		for (const auto& animPair : animationsIterator->second)
			pAvatar->AddAnimation(animPair.first, animPair.second);

		return pAvatar;
	}

	return nullptr;
}

TextSprite* TextureManager::CreateText(const std::string& text, const Point2f& pivot, int fontSize, const Color4f& color)
{
	const std::string fontPath{ "./Font/BodoniModa-VariableFont_opsz,wght.ttf" };
	TextSprite* pText{ new TextSprite{ text, fontPath, fontSize, color } };
	pText->SetPivot(pivot);
	return pText;
}

TextSprite* TextureManager::CreateText(int number, const Point2f& pivot, int fontSize, const Color4f& color)
{
	return CreateText(std::to_string(number), pivot, fontSize, color);
}
