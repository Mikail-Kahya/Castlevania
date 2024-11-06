#include "pch.h"
#include "StatBar.h"
#include "Player.h"
#include "GUIBar.h"
#include "GUIFrame.h"
#include "GUIMana.h"
#include "GUICounter.h"
#include "myUtils.h"

StatBar::StatBar(const nlohmann::json& data)
{
	const std::string id{ data["type"] };
	Texture* pTexture{ GetTextureManager().GetTexture(id) };
	const float scale{ GetTextureManager().GetScale(id) };

	for (const auto& object : data["GUIElements"])
	{
		const std::string type{ object["type"] };
		const std::string id{ object["id"] };
		const Point2f position{ object["pos"]["x"], object["pos"]["y"] };
		if (type == "counter")
		{
			// uses pivot coordinates
			m_pUIElementMap[id] = new GUICounter{ position };
			continue;
		}

		// uses bottomLeft
		BasicSprite* pSprite{ new BasicSprite{pTexture, position, scale} };

		const Rectf srcRect{ object["src"]["x"], object["src"]["y"],
							object["src"]["w"] , object["src"]["h"] };
		pSprite->SetSrcRect(srcRect);
		
		if (type == "frame")
			m_pUIElementMap[id] = new GUIFrame{ pSprite };
		else if (type == "bar")
			m_pUIElementMap[id] = new GUIBar{ pSprite, srcRect };
		else if (type == "mana")
			m_pUIElementMap[id] = new GUIMana{ pSprite };
	}
}

StatBar::~StatBar()
{
	for (const auto& pUIElement : m_pUIElementMap)
		delete pUIElement.second;
}

void StatBar::Draw() const
{
	for (const auto& pUIElement : m_pUIElementMap)
		pUIElement.second->Draw();
}

void StatBar::Update(float deltaTime)
{
	const Stats playerStats{ GetPlayer()->GetStats() };
	const Stats maxPlayerStats{ GetPlayer()->GetMaxStats() };

	for (const auto& pUIElement : m_pUIElementMap)
	{
		GUIStat* pUIStat{ dynamic_cast<GUIStat*>(pUIElement.second) };
		if(pUIStat)
		{
			int stat{};
			int maxStat{};
			if (pUIElement.first == "health" || pUIElement.first == "healthCounter")
			{
				stat = playerStats.hp;
				maxStat = maxPlayerStats.hp;
			}
			else if (pUIElement.first == "stamina")
			{
				stat = int(playerStats.stamina);
				maxStat = int(maxPlayerStats.stamina);
			}
			else if (pUIElement.first == "mana" || pUIElement.first == "manaCounter")
			{
				stat = playerStats.mana;
				maxStat = maxPlayerStats.mana;
			}
			pUIStat->SetMaxStat(maxStat);
			pUIStat->Update(stat, deltaTime);
		}
	}
}