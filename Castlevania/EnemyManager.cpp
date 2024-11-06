#include "pch.h"
#include "EnemyManager.h"
#include "Level.h"
#include "Player.h"
#include "Bat.h"
#include "Ghost.h"
#include "Zombie.h"
#include "SkeletonRanged.h"
#include "Banshee.h"
#include "Arthroverta.h"
#include "Weapon.h"
#include "myUtils.h"

std::map<std::string, EntityData> EnemyManager::m_EnemyStatsMap{};

EnemyManager::EnemyManager()
{
	LoadStatics();
}

EnemyManager::~EnemyManager()
{
	ClearEnemies();
}

void EnemyManager::LoadStatics()
{
	if (!m_EnemyStatsMap.empty()) return;

	nlohmann::json data{};
	myUtils::ParseJson("./Manager/EnemyManager.json", data);

	m_Spawns = data["spawns"];

	for (const auto& statsData : data["stats"])
		m_EnemyStatsMap.insert({ statsData["id"], EntityData{statsData} });
}

void EnemyManager::Update(float deltaTime)
{
	if (Level::RoomChanged())
	{
		ClearEnemies();
		CreateEnemies(Level::GetBounds(), Level::GetActiveRoom());
	}

	const Weapon* pPlayerWeapon{ GetPlayer()->GetActiveWeapon() };
	for (int index{}; index < m_pEnemyVec.size(); ++index)
	{
		Enemy* pEnemy{ m_pEnemyVec[index] };

		if (pPlayerWeapon)
		{
			const Rectf playerHitBox{ pPlayerWeapon->GetHitbox() };
			const int playerDamage{ pPlayerWeapon->GetDamage() + GetPlayer()->GetStats().damage };
			pEnemy->Hurt(playerHitBox, playerDamage);
		}

		pEnemy->Update(deltaTime);

		if (!utils::IsOverlapping(pEnemy->GetHurtBox(), Level::GetBounds()))
		{
			DeleteEnemy(index);
			continue;
		}

		if (pEnemy->AllowDelete())
		{
			GetPlayer()->AddExp(pEnemy->GetExp());
			DeleteEnemy(index);
		}
	}
}

void EnemyManager::Draw() const
{
	for (Enemy* pEnemy : m_pEnemyVec)
		pEnemy->Draw();
}

void EnemyManager::CreateEnemies(const Rectf& bounds, int activeRoom)
{
	for (const auto& object : m_Spawns[activeRoom]["spawns"])
	{
		const std::string id{ object["type"] };
		const EntityData enemyStats{ m_EnemyStatsMap[id] };
		Point2f pivot{ object["x"], object["y"] };
		pivot.x += bounds.left;
		pivot.y += bounds.bottom;

		if (id == "bat")
			m_pEnemyVec.push_back(new Bat{ pivot, enemyStats });
		else if (id == "zombie")
			m_pEnemyVec.push_back(new Zombie{ pivot, enemyStats });
		else if (id == "skeletonRanged")
			m_pEnemyVec.push_back(new SkeletonRanged{ pivot, enemyStats });
		else if (id == "ghost")
			m_pEnemyVec.push_back(new Ghost{ pivot, enemyStats });
		else if (id == "banshee")
			m_pEnemyVec.push_back(new Banshee{ pivot, enemyStats});
		else if (id == "arthroverta")
			m_pEnemyVec.push_back(new Arthroverta{ pivot, enemyStats });
	}
}	

void EnemyManager::ClearEnemies()
{
	for (Enemy* pEnemy : m_pEnemyVec)
		delete pEnemy;
	
	m_pEnemyVec.clear();
}

void EnemyManager::DeleteEnemy(int index)
{
	// switch element at index and last position
	const int lastIndex{ int(m_pEnemyVec.size()) - 1 };

	Enemy* pTemp{ m_pEnemyVec[lastIndex] };
	m_pEnemyVec[lastIndex] = m_pEnemyVec[index];
	m_pEnemyVec[index] = pTemp;

	// remove element from vector
	delete m_pEnemyVec[lastIndex];
	m_pEnemyVec.pop_back();
}