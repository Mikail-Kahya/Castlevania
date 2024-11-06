#pragma once
#include "Room.h"
#include <map>
class Enemy;

class Stone : public Room
{
public:
	Stone(const nlohmann::json& data);
	virtual ~Stone() = default;

	Stone(const Stone& other) = delete;
	Stone& operator=(const Stone& other) = delete;
	Stone(Stone&& other) noexcept = delete;
	Stone& operator=(Stone&& other) noexcept = delete;

private:
	void CreateBase() override;
	void CreateBackgrounds();
	void CreateFloors();
	void CreateCeilings();

	static bool m_Loaded;
	static std::map<std::string, Tile> m_TileMap;
};

