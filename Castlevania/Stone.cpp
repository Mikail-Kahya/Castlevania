#include "pch.h"
#include "Stone.h"
#include "Texture.h"

bool Stone::m_Loaded{ false };
std::map<std::string, Tile> Stone::m_TileMap{};

Stone::Stone(const nlohmann::json& data)
{
	if (!m_Loaded)
	{
		CreateTiles("stone", m_TileMap);
		m_Loaded = true;
	}
	CreateRoom(data, m_TileMap);
}

void Stone::CreateBase()
{
	CreateBackgrounds();
	CreateFloors();
	CreateCeilings();
}

void Stone::CreateBackgrounds()
{
	Texture* pBackground{ m_TileMap["Background"].pTexture };
	Point2f bottomLeft{ m_Bounds.left,
						m_Bounds.bottom + 24 };

	// fill room with backgrounds
	bool reachedEnd{ false };
	while (!reachedEnd)
	{
		AddTile(pBackground, bottomLeft);

		bottomLeft.x += pBackground->GetWidth();
		if (bottomLeft.x > m_Bounds.left + m_Bounds.width)
		{
			reachedEnd = true;
		}
	}
}

void Stone::CreateFloors()
{
	const int maxFloors{ 3 };
	int floorIndex{ 0 };

	Point2f bottomLeft{ m_Bounds.left, m_Bounds.bottom };

	// fill room with floor tiles
	bool reachedEnd{ false };
	while (!reachedEnd)
	{
		const int idNumber{ floorIndex % maxFloors };
		const std::string id{ "Floor" + std::to_string(idNumber) };

		Texture* pFloor{ m_TileMap[id].pTexture };

		AddTile(pFloor, bottomLeft);
		bottomLeft.x += pFloor->GetWidth();
		++floorIndex;
		if (bottomLeft.x > m_Bounds.left + m_Bounds.width)
		{
			reachedEnd = true;
		}
	}
}

void Stone::CreateCeilings()
{
	const int maxCeilings{ 2 };
	int ceilingIndex{ 0 };

	Point2f topLeft{ m_Bounds.left, m_Bounds.bottom + m_Bounds.height };

	// fill room with ceilings
	bool reachedEnd{ false };
	while (!reachedEnd)
	{
		const int idNumber{ ceilingIndex % maxCeilings };
		const std::string id{ "Ceiling" + std::to_string(idNumber) };

		Texture* pCeiling{ m_TileMap[id].pTexture };
		const Point2f bottomLeft{ topLeft.x, topLeft.y - pCeiling->GetHeight() };

		AddTile(pCeiling, bottomLeft);
		topLeft.x += pCeiling->GetWidth();
		++ceilingIndex;
		if (topLeft.x > m_Bounds.left + m_Bounds.width)
		{
			reachedEnd = true;
		}
	}
}
