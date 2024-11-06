#include "pch.h"
#include "Sandstone.h"
#include "Texture.h"

bool Sandstone::m_Loaded{ false };
std::map<std::string, Tile> Sandstone::m_TileMap{};

Sandstone::Sandstone(const nlohmann::json& data)
{
	if (!m_Loaded)
	{
		CreateTiles("sandstone", m_TileMap);
		m_Loaded = true;
	}
	CreateRoom(data, m_TileMap);
}

void Sandstone::CreateBase()
{
	CreateBackgrounds();
	CreateWalls();
	CreateFloors();
}

void Sandstone::CreateBackgrounds()
{
	Texture* pBackground{ m_TileMap["Background"].pTexture };
	Point2f bottomLeft{ m_Bounds.left + m_TileMap["Wall"].pTexture->GetWidth(),
						m_Bounds.bottom + m_TileMap["Floor"].pTexture->GetHeight() };
	
	// fill the screen with backgrounds
	bool reachedEnd{ false };
	while (!reachedEnd)
	{
		AddTile(pBackground, bottomLeft);

		bottomLeft.y += pBackground->GetHeight();
		if (bottomLeft.y > m_Bounds.bottom + m_Bounds.height)
		{
			reachedEnd = true;
		}
	}
}

void Sandstone::CreateFloors()
{
	Texture* pFloor{ m_TileMap["Floor"].pTexture };
	Point2f bottomLeft{ m_Bounds.left, m_Bounds.bottom };

	// fill screen with floors (at top and bottom of the room)
	bool reachedEnd{ false };
	while (!reachedEnd)
	{
		const float ceilingX{ bottomLeft.x };
		const float ceilingY{ bottomLeft.y + m_Bounds.height - pFloor->GetHeight() };

		AddTile(pFloor, bottomLeft);
		AddTile(pFloor, Point2f{ ceilingX, ceilingY });

		bottomLeft.x += pFloor->GetWidth();
		if (bottomLeft.x > m_Bounds.left + m_Bounds.width)
		{
			reachedEnd = true;
		}
	}
}

void Sandstone::CreateWalls()
{
	Texture* pWall{ m_TileMap["Wall"].pTexture };
	Point2f bottomLeft{ m_Bounds.left, m_Bounds.bottom };

	// fill screen with walls (at left and right of the room)
	bool reachedEnd{ false };
	while (!reachedEnd)
	{
		const float rightX{ bottomLeft.x + m_Bounds.width - pWall->GetWidth() };
		const float rightY{ bottomLeft.y };

		AddTile(pWall, bottomLeft, false);
		AddTile(pWall, Point2f{ rightX, rightY }, true);

		bottomLeft.y += pWall->GetHeight();
		if (bottomLeft.y > m_Bounds.bottom + m_Bounds.height)
		{
			reachedEnd = true;
		}
	}
}