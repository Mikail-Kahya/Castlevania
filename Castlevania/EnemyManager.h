#pragma once
#include "myUtils.h"
class Particle;
class PickUp;
class Enemy;
class Player;

class EnemyManager final
{
public:
	EnemyManager();
	~EnemyManager();

	EnemyManager(const EnemyManager& other) = delete;
	EnemyManager& operator=(const EnemyManager& other) = delete;
	EnemyManager(EnemyManager&& other) noexcept = delete;
	EnemyManager& operator=(EnemyManager&& other) noexcept = delete;

	void Update(float deltaTime);
	void Draw() const;

private:
	void LoadStatics();

	void CreateEnemies(const Rectf& bounds, int activeRoom);
	void ClearEnemies();
	void DeleteEnemy(int index);

	static std::map<std::string, EntityData> m_EnemyStatsMap;
	nlohmann::json m_Spawns{};
	std::vector<Enemy*> m_pEnemyVec{};
};