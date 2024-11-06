#include "pch.h"
#include "PickUpManager.h"
#include "PickUp.h"
#include "Level.h"

PickUpManager::~PickUpManager()
{
	ClearVector();
}

void PickUpManager::Draw() const
{
	for (PickUp* pPickUp : m_pPickUpVec)
		pPickUp->Draw();
}

void PickUpManager::Update(float deltaTime)
{
	if (Level::RoomChanged())
		ClearVector();

	for (int index{}; index < m_pPickUpVec.size(); ++index)
	{
		PickUp* pPickUp{ m_pPickUpVec[index] };

		pPickUp->Update(deltaTime);
		if (pPickUp->Collect())
			DeletePickUp(index);
	}
}

void PickUpManager::AddPickUp(PickUp* pPickUp)
{
	if (!pPickUp) return;
	m_pPickUpVec.push_back(pPickUp);
}

void PickUpManager::ClearVector()
{
	for (PickUp* pPickUp : m_pPickUpVec)
		delete pPickUp;
	
	m_pPickUpVec.clear();
}

void PickUpManager::DeletePickUp(int index)
{
	// switch element at index and last position
	const int lastIndex{ int(m_pPickUpVec.size()) - 1 };
	PickUp* pTemp{ m_pPickUpVec[lastIndex] };
	m_pPickUpVec[lastIndex] = m_pPickUpVec[index];
	m_pPickUpVec[index] = pTemp;

	// remove element from vector
	delete m_pPickUpVec[lastIndex];
	m_pPickUpVec.pop_back();
}
