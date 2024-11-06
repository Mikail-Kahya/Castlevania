#include "pch.h"
#include "Brick.h"
#include "Texture.h"

bool Brick::m_Loaded{ false };
std::map<std::string, Tile> Brick::m_TileMap{};

Brick::Brick(const nlohmann::json& data)
{
	if (!m_Loaded)
	{
		CreateTiles("brick", m_TileMap);
		m_Loaded = true;
	}
	CreateRoom(data, m_TileMap);
}

void Brick::CreateBase()
{
	CreateBackgrounds();
	CreateFloors();
	CreateCeilings();
}

void Brick::CreateBackgrounds()
{
	Tile bgTile{ m_TileMap["Background"] };
	Point2f bottomLeft{ m_Bounds.left,
						m_Bounds.bottom + m_TileMap["Floor0"].pTexture->GetHeight() };
	
	// fill the screen with backgrounds
	bool reachedEnd{ false };
	while (!reachedEnd)
	{
		AddTile(bgTile.pTexture, bottomLeft, bgTile.animation);

		bottomLeft.x += bgTile.pTexture->GetWidth() / bgTile.animation.cols;
		if (bottomLeft.x > m_Bounds.left + m_Bounds.width)
		{
			reachedEnd = true;
		}
	}
}

void Brick::CreateFloors()
{
	const int maxFloors{ 2 };
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

void Brick::CreateCeilings()
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