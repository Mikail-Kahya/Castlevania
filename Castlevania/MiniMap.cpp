#include "pch.h"
#include "MiniMap.h"
#include "Game.h"
#include "Player.h"
#include "GUIFrame.h"

MiniMap::MiniMap(const nlohmann::json& data)
{
	m_BottomLeft = Point2f{ data["position"]["x"],
							data["position"]["y"] };
	m_pFrame = new GUIFrame{ GetTextureManager().CreateSprite(data["type"]), 0.8f};
	LoadVisitedRooms();
}

MiniMap::~MiniMap()
{
	delete m_pFrame;
}

void MiniMap::Draw() const
{
	glPushMatrix();
	glTranslatef(m_BottomLeft.x, m_BottomLeft.y, 0);

	m_pFrame->Draw();

	const float margin{ 20 };
	glTranslatef(margin, margin, 0);
	DrawRooms();
	DrawDot();

	glPopMatrix();

	glColor4f(1, 1, 1, 1);
}

void MiniMap::Update(float deltaTime)
{
	if (Level::RoomChanged())
		AddRoom();
}

void MiniMap::Save(nlohmann::json& data)
{
	for (const Rectf& room : m_RoomVec)
	{
		nlohmann::json roomData{};
		roomData["x"] = room.left;
		roomData["y"] = room.bottom;
		roomData["w"] = room.width;
		roomData["h"] = room.height;
		data.push_back(roomData);
	}
}

void MiniMap::Reset()
{
	m_RoomVec.clear();
}

void MiniMap::LoadVisitedRooms()
{
	const nlohmann::json data{ Game::GetSavedData() };

	if (!data.contains("hud")) return;
	if (!data["hud"].contains("roomsVisited")) return;

	for (const auto& roomObject : data["hud"]["roomsVisited"])
	{
		Rectf room{ roomObject["x"], roomObject["y"]
						, roomObject["w"], roomObject["h"] };
		m_RoomVec.push_back(room);
	}
}

void MiniMap::DrawRooms() const
{
	const Color4f fill{ 0.4f, 0.4f, 0.4f, m_pFrame->GetOpacity() };
	const Color4f stroke{ 0.8f, 0.8f, 0.8f, m_pFrame->GetOpacity() };
	const float strokeWidth{ 2 };

	for (const Rectf& room : m_RoomVec)
	{
		utils::SetColor(fill);
		utils::FillRect(room);
		utils::SetColor(stroke);
		utils::DrawRect(room, strokeWidth);
	}
}

void MiniMap::DrawDot() const
{
	const Rectf activeRoom{ m_RoomVec[m_ActiveRoom] };
	Point2f dotCenter{ activeRoom.left, activeRoom.bottom };
	dotCenter.x += activeRoom.width / 2;
	dotCenter.y += activeRoom.height / 2;

	const float dotRadius{ 5 };
	const Color4f dotColor{ 0.7f, 0.2f, 0.2f, m_pFrame->GetOpacity() };
	utils::SetColor(dotColor);
	utils::FillEllipse(dotCenter, dotRadius, dotRadius);
}

void MiniMap::AddRoom()
{
	Rectf newRoom{ Level::GetBounds() };
	newRoom.left /= m_ScaleDown;
	newRoom.bottom /= m_ScaleDown;
	newRoom.width /= m_ScaleDown;
	newRoom.height /= m_ScaleDown;

	const float epsilon{ 0.005f };
	for (int index{}; index < m_RoomVec.size(); ++index)
	{
		const Rectf room{ m_RoomVec[index] };
		if (abs(room.left - newRoom.left) > epsilon)
			continue;

		if (abs(room.bottom - newRoom.bottom) > epsilon)
			continue;

		if (abs(room.width - newRoom.width) > epsilon)
			continue;

		if (abs(room.height - newRoom.height) > epsilon)
			continue;

		m_ActiveRoom = index;
		return;
	}

	m_RoomVec.push_back(newRoom);
	m_ActiveRoom = int(m_RoomVec.size()) - 1;
}