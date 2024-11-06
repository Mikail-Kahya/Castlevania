#pragma once
#include <vector>
class Room;
class Player;

using vertexCollection = std::vector<std::vector<Point2f>>;
using vertexShape = std::vector<Point2f>;

class Level final
{
public:
	explicit Level();
	~Level();
	
	Level(const Level& other) = delete;
	Level& operator=(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(Level&& other) noexcept = delete;

	void Draw() const;
	void Update(float deltaTime);

	static const Rectf& GetBounds();
	static int GetActiveRoom();
	static bool RoomChanged();
	static void Reset();
	static int GetAmountRooms();

private:
	void Setup();
	void CreateCollision();
	void CreatePlatforms();
	void CreateRooms();

	void ChangeRoom();

	static const vertexCollection& GetCollisions();
	static const vertexCollection& GetPlatforms();
	friend class RigidBody;

	static int m_ActiveRoom;
	static Rectf m_Bounds;
	static bool m_ChangeRoom;
	static vertexCollection m_CollisionsVec;
	static vertexCollection m_PlatformVec;

	std::vector<Room*> m_pRoomVec{};
};