#include "pch.h"
#include "Room.h"
#include "Magnet.h"
#include "SavePoint.h"
#include "myUtils.h"

Room::~Room()
{
	for (Sprite* pTexture : m_TileVec)
		delete pTexture;
	for (MapMechanic* pMechanic : m_pMechanicVec)
		delete pMechanic;
}

void Room::Draw() const
{
	for (Sprite* pSprite: m_TileVec)
		pSprite->Draw();

	for (MapMechanic* pMapMechanic : m_pMechanicVec)
		pMapMechanic->Draw();
}

void Room::Update(float deltaTime)
{
	for (Sprite* pSprite : m_TileVec)
		pSprite->Update(deltaTime);

	for (MapMechanic* pMapMechanic : m_pMechanicVec)
		pMapMechanic->Update(deltaTime);
}

const Rectf& Room::GetBounds() const
{
	return m_Bounds;
}

void Room::CreateTiles(const std::string& type, std::map<std::string, Tile>& tileMap)
{
	const std::string filePath{ "Level/Tilesets.json" };
	nlohmann::json data{};
	myUtils::ParseJson(filePath, data);

	const std::string folderPath{ data[type]["path"] };
	for (auto& object : data[type]["tiles"])
	{
		const std::string id{ object["id"] };
		const std::string type{ object["type"] };
		const std::string imagePath{ folderPath + id + type };
		Texture* pTexture{ new Texture{ imagePath } };
		Anim animation{};
		if (object.contains("anim"))
			animation = myUtils::CreateAnim(object["anim"]);
		tileMap[id] = Tile{ pTexture, animation };
	}
}

void Room::AddTile(Texture* pTexture, const Point2f& bottomLeft, bool flip)
{
	BasicSprite* pTile{ new BasicSprite{ pTexture, bottomLeft } };
	pTile->SetFlip(flip);
	m_TileVec.push_back(pTile);
}

void Room::AddTile(Texture* pTexture, const Point2f& bottomLeft, const Anim& animation, bool flip)
{
	AnimatedSprite* pTile{ new AnimatedSprite{ pTexture, animation, bottomLeft } };
	pTile->SetPosition(bottomLeft);
	pTile->SetFlip(flip);
	m_TileVec.push_back(pTile);
}

void Room::CreateBounds(const nlohmann::json& data)
{
	nlohmann::json boundsData{ data["bounds"] };

	const Rectf boundaries{ boundsData["x"], boundsData["y"],
							boundsData["w"], boundsData["h"] };
	m_Bounds = boundaries;
}

void Room::CreateObjects(const nlohmann::json& data, std::map<std::string, Tile>& tileMap)
{
	for (auto& object : data)
	{
		const std::string id{ object["id"] };

		const Tile tile{ tileMap[id] };

		const float x{ m_Bounds.left + float(object["x"]) };
		const float y{ m_Bounds.bottom + (m_Bounds.height - float(object["y"]) - tile.pTexture->GetHeight()) };
		const Point2f bottomLeft{ x, y };
		
		const bool flip{ object["flipped"] };

		if (tile.animation.nrFrames != 0)
			AddTile(tile.pTexture, bottomLeft, tile.animation, flip);
		else
			AddTile(tile.pTexture, bottomLeft, flip);
	}
}

void Room::CreateMechanics(const nlohmann::json& data)
{
	for (auto& object : data)
	{
		const int type{ object["type"] };
		const float x{ m_Bounds.left + float(object["x"]) };
		const float y{ m_Bounds.bottom + (m_Bounds.height - float(object["y"])) };
			
		switch (type)
		{
		case 0:
			m_pMechanicVec.push_back(new Magnet{ Point2f{x, y} });
			break;
		case 1:
			m_pMechanicVec.push_back(new SavePoint{ Point2f{x, y} });
			break;
		}
	}
}

void Room::CreateRoom(const nlohmann::json& data, std::map<std::string, Tile>& tileMap)
{
	CreateBounds(data);
	CreateBase();
	CreateObjects(data["objects"], tileMap);
	if (data.contains("mechanics"))
		CreateMechanics(data["mechanics"]);
}
