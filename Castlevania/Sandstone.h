#pragma once
#include "Room.h"
class Texture;

class Sandstone : public Room
{
public:
	Sandstone(const nlohmann::json& data);
	virtual ~Sandstone() = default;

	Sandstone(const Sandstone& other) = delete;
	Sandstone& operator=(const Sandstone& other) = delete;
	Sandstone(Sandstone&& other) noexcept = delete;
	Sandstone& operator=(Sandstone&& other) noexcept = delete;

private:
	void CreateBase() override;
	void CreateBackgrounds();
	void CreateFloors();
	void CreateWalls();

	static bool m_Loaded;
	static std::map<std::string, Tile> m_TileMap;
};

