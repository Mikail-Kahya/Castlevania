#pragma once
#include "HUDElement.h"
class GUIFrame;

class MiniMap : public HUDElement
{
public:
	MiniMap(const nlohmann::json& data);
	virtual ~MiniMap() override;

	MiniMap(const MiniMap& other) = delete;
	MiniMap& operator=(const MiniMap& other) = delete;
	MiniMap(MiniMap&& other) noexcept = delete;
	MiniMap& operator=(MiniMap&& other) noexcept = delete;

	void Draw() const override;
	void Update(float deltaTime) override;
	void Save(nlohmann::json& data) override;
	void Reset() override;

private:
	void LoadVisitedRooms();

	void DrawRooms() const;
	void DrawDot() const;
	void AddRoom();

	Point2f m_BottomLeft{};
	std::vector<Rectf> m_RoomVec{};
	GUIFrame* m_pFrame{};
	const float m_ScaleDown{ 30 };
	int m_ActiveRoom{};
};