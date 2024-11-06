#include "pch.h"
#include "debugPch.h"
#include "Level.h"
#include "Brick.h"
#include "Stone.h"
#include "Sandstone.h"
#include "Player.h"
#include "SVGParser.h"
#include "utils.h"
#include "myUtils.h"

int Level::m_ActiveRoom{ -1 };
Rectf Level::m_Bounds{};
bool Level::m_ChangeRoom{ true };
vertexCollection Level::m_CollisionsVec{};
vertexCollection Level::m_PlatformVec{};

Level::Level()
{
	Setup();
}

Level::~Level()
{
	for (Room* pRoom : m_pRoomVec)
		delete pRoom;
}

void Level::Draw() const
{
	m_pRoomVec[m_ActiveRoom]->Draw();

#ifdef _DEBUG_COLLISION
	glColor4f(1, 1, 1, 1);
	for (const vertexShape& vertVec : m_CollisionsVec)
		utils::DrawPolygon(vertVec, true, 5);

	for (const vertexShape& platform : m_PlatformVec)
		utils::DrawPolygon(platform, false, 5);
#endif
}

void Level::Update(float deltaTime)
{
	const int tempRoom{ m_ActiveRoom };
	for (int index{}; index < m_pRoomVec.size(); ++index)
	{
		Rectf bounds{ m_pRoomVec[index]->GetBounds() };
		if (utils::IsPointInRect(GetPlayer()->GetPivot(), bounds)) 
			m_ActiveRoom = index;
	}

	m_ChangeRoom = m_ActiveRoom != tempRoom;
	ChangeRoom();
	m_pRoomVec[m_ActiveRoom]->Update(deltaTime);
}

const Rectf& Level::GetBounds()
{
	return m_Bounds;
}

const vertexCollection& Level::GetCollisions()
{
	return m_CollisionsVec;
}

const vertexCollection& Level::GetPlatforms()
{
	return m_PlatformVec;
}

int Level::GetActiveRoom()
{
	return m_ActiveRoom;
}

bool Level::RoomChanged()
{
	return m_ChangeRoom;
}

void Level::Reset()
{
	m_ActiveRoom = -1;
	m_ChangeRoom = true;
}

void Level::Setup()
{
	CreateCollision();
	CreatePlatforms();
	CreateRooms();
}

void Level::CreateCollision()
{
	const std::string svgPath{ "Level/Level.svg" };
	SVGParser::GetVerticesFromSvgFile(svgPath, m_CollisionsVec);
}

void Level::CreatePlatforms()
{
	const std::string svgPath{ "Level/Platforms.svg" };
	SVGParser::GetVerticesFromSvgFile(svgPath, m_PlatformVec);
}

void Level::CreateRooms()
{
	nlohmann::json jsonData;
	myUtils::ParseJson("Level/Rooms.json", jsonData);
	for (auto roomObject : jsonData["rooms"])
	{
		const int type{ roomObject["type"] };
		switch (type)
		{
		case 0:
			m_pRoomVec.push_back(new Stone{ roomObject });
			break;
		case 1:
			m_pRoomVec.push_back(new Sandstone{ roomObject });
			break;
		case 2:
			m_pRoomVec.push_back(new Brick{ roomObject });
			break;
		}
	}
}

void Level::ChangeRoom()
{
	if (!m_ChangeRoom) return;
	GetSoundManager().StopEffects();
	m_Bounds = m_pRoomVec[m_ActiveRoom]->GetBounds();
}
