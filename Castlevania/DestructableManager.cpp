#include "pch.h"
#include "DestructableManager.h"
#include "Lantern.h"
#include "Level.h"
#include "Weapon.h"
#include "myUtils.h"

DestructableManager::DestructableManager()
{
	myUtils::ParseJson("./Manager/DestructableManager.json", m_Data);
}

DestructableManager::~DestructableManager()
{
	ClearDestructables();
}

void DestructableManager::Update(PickUpManager& pickUpManager, float deltaTime)
{
	if (Level::RoomChanged())
	{
		ClearDestructables();
		CreateDestructables(Level::GetBounds(), Level::GetActiveRoom());
	}

	const Weapon* pPlayerWeapon{ GetPlayer()->GetActiveWeapon() };
	for (int index{}; index < m_pDestructableVec.size(); ++index)
	{
		Destructable* pDestructable{ m_pDestructableVec[index] };

		if (pPlayerWeapon)
			pDestructable->Hurt(pPlayerWeapon->GetHitbox());

		pDestructable->Update(deltaTime);

		if (pDestructable->AllowDelete())
		{
			pickUpManager.AddPickUp(pDestructable->SpawnPickUp());
			DeleteDestructable(index);
		}
	}
}

void DestructableManager::Draw() const
{
	for (Destructable* pDestructable : m_pDestructableVec)
		pDestructable->Draw();
}

void DestructableManager::CreateDestructables(const Rectf& bounds, int activeRoom)
{
	for (const auto& object : m_Data[activeRoom]["spawns"])
	{
		const std::string type{ object["type"] };
		Point2f pivot{ object["x"], object["y"] };
		pivot.x += bounds.left;
		pivot.y += bounds.bottom;

		if (type == "lantern")
			m_pDestructableVec.push_back(new Lantern{ pivot });
	}
}

void DestructableManager::ClearDestructables()
{
	for (Destructable* pDestructable : m_pDestructableVec)
		delete pDestructable;
	
	m_pDestructableVec.clear();
}

void DestructableManager::DeleteDestructable(int index)
{
	// switch element at index and last position
	const int lastIndex{ int(m_pDestructableVec.size()) - 1 };
	Destructable* pTemp{ m_pDestructableVec[lastIndex] };
	m_pDestructableVec[lastIndex] = m_pDestructableVec[index];
	m_pDestructableVec[index] = pTemp;

	// remove element from vector
	delete m_pDestructableVec[lastIndex];
	m_pDestructableVec.pop_back();
}
