#pragma once
#include "Room.h"
class Texture;

class Brick : public Room
{
public:
	Brick(const nlohmann::json& data);
	virtual ~Brick() = default;

	Brick(const Brick& other) = delete;
	Brick& operator=(const Brick& other) = delete;
	Brick(Brick&& other) noexcept = delete;
	Brick& operator=(Brick&& other) noexcept = delete;

private:
	void CreateBase() override;
	void CreateBackgrounds();
	void CreateFloors();
	void CreateCeilings();

	static bool m_Loaded;
	static std::map<std::string, Tile> m_TileMap;
};