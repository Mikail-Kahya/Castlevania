#pragma once
#include "myStructs.h"
#include <map>
#include <vector>
class Player;
class MapMechanic;
class Sprite;
class Texture;

class Room
{
public:
	virtual ~Room();

	Room(const Room& other) = delete;
	Room& operator=(const Room& other) = delete;
	Room(Room&& other) noexcept = delete;
	Room& operator=(Room&& other) noexcept = delete;

	virtual void Draw() const;
	void Update(float deltaTime);
	const Rectf& GetBounds() const;

protected:
	Room() = default;

	void CreateRoom(const nlohmann::json& data, std::map<std::string, Tile>& tileMap);
	void CreateTiles(const std::string& type, std::map<std::string, Tile>& tileMap);
	void AddTile(Texture* pTexture, const Point2f& bottomLeft, bool flip = false);
	void AddTile(Texture* pTexture, const Point2f& bottomLeft, const Anim& animation, bool flip = false);

	Rectf m_Bounds{};

private:
	void CreateBounds(const nlohmann::json& data);
	virtual void CreateBase() = 0;
	void CreateObjects(const nlohmann::json& data, std::map<std::string, Tile>& tileMap);
	void CreateMechanics(const nlohmann::json& data);

	std::vector<MapMechanic*> m_pMechanicVec{};
	std::vector<Sprite*> m_TileVec;
	std::vector<Point2f> m_SpawnVec;
};