#include "pch.h"
#include "HUD.h"
#include "StatBar.h"
#include "MiniMap.h"
#include "myUtils.h"
#include "fstream"

HUD::~HUD()
{
	for (HUDElement* pHUDElement : m_pHUDElementVec)
		delete pHUDElement;
}

void HUD::AddElement(const nlohmann::json& data)
{
	HUDElement* pHUDElement{ nullptr };

	if (data["type"] == "statBar")
		pHUDElement = new StatBar{ data };
	else if (data["type"] == "miniMap")
		pHUDElement = new MiniMap{ data };
	
	m_pHUDElementVec.push_back(pHUDElement);
}

void HUD::Setup()
{
	nlohmann::json data{};
	myUtils::ParseJson("./UI/Json/HUD.json", data);

	for (const auto& object : data)
		AddElement(object);
}

void HUD::Update(float deltaTime)
{
	for (HUDElement* pHUDElement : m_pHUDElementVec)
		pHUDElement->Update(deltaTime);
}

void HUD::Draw() const
{
	for (HUDElement* pHUDElement : m_pHUDElementVec)
		pHUDElement->Draw();
}

nlohmann::json HUD::Save() const
{
	nlohmann::json data{};
	m_pHUDElementVec[1]->Save(data["roomsVisited"]);
	return data;
}

void HUD::Reset() const
{
	for (int index{}; index < m_pHUDElementVec.size(); ++index)
		m_pHUDElementVec[index]->Reset();
}