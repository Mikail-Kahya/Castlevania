#include "pch.h"
#include "Equipment.h"
#include "Player.h"
#include "ThrowableWeapon.h"

Equipment::~Equipment()
{
	for (auto& pWeapon : m_pWeaponMap)
		delete pWeapon.second;

	for (ThrowableWeapon* pThrowableWeapon : m_pThrowableWeaponVec)
		delete pThrowableWeapon;
}

void Equipment::Draw() const
{
	for (ThrowableWeapon* pThrowableWeapon : m_pThrowableWeaponVec)
		pThrowableWeapon->Draw();

	if (m_pActiveWeapon)
		m_pActiveWeapon->Draw();
}

void Equipment::Update(Entity* pEntity, float deltaTime)
{
	for (auto& pWeapon : m_pWeaponMap)
		pWeapon.second->Update(pEntity, deltaTime);

	for (ThrowableWeapon*& pThrowableWeapon : m_pThrowableWeaponVec)
	{
		pThrowableWeapon->Update(pEntity, deltaTime);

		if (pThrowableWeapon->AllowDelete())
		{
			ThrowableWeapon* temp{ m_pThrowableWeaponVec.back() };
			delete pThrowableWeapon;
			pThrowableWeapon = temp;
			m_pThrowableWeaponVec.pop_back();
		}
	}

	CheckSelfDisable();
}

void Equipment::ThrowWeapon(ThrowableWeapon* pThrowableWeapon)
{
	m_pThrowableWeaponVec.push_back(pThrowableWeapon);
}

bool Equipment::AddWeapon(const std::string& id, Weapon* pWeapon)
{
	const size_t mapSize{ m_pWeaponMap.size() };
	m_pWeaponMap.insert({ id, pWeapon });
	return mapSize != m_pWeaponMap.size();
}

bool Equipment::DeleteWeapon(const std::string& id)
{
	const auto iterator{ m_pWeaponMap.find(id) };
	if (iterator != m_pWeaponMap.end())
		return DeleteWeapon(iterator);
	return false;
}

const std::vector<ThrowableWeapon*>& Equipment::GetThrowableWeapons() const
{
	return m_pThrowableWeaponVec;
}

Weapon* Equipment::GetActiveWeapon() const
{
	return m_pActiveWeapon;
}

bool Equipment::SetActiveWeapon(const std::string& id, float delay)
{
	m_pActiveWeapon = m_pWeaponMap[id];

	if (!m_pActiveWeapon->Use(delay))
	{
		m_pActiveWeapon = nullptr;
		return false;
	}
	return true;
}

void Equipment::DisableActiveWeapon()
{
	if (!m_pActiveWeapon) return;
	m_pActiveWeapon->Disable();
	m_pActiveWeapon = nullptr;
}

void Equipment::CheckSelfDisable()
{
	if (!m_pActiveWeapon) return;
	if (!m_pActiveWeapon->IsActive())
		m_pActiveWeapon = nullptr;
}

bool Equipment::DeleteWeapon(const std::map<std::string, Weapon*>::iterator& iterator)
{
	delete iterator->second;
	m_pWeaponMap.erase(iterator);
	return true;
}