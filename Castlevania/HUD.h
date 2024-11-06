#pragma once
#include "HUDElement.h"

class HUD final
{
public:
	HUD() = default;
	~HUD();

	HUD(const HUD& other) = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD(HUD&& other) noexcept = delete;
	HUD& operator=(HUD&& other) noexcept = delete;

	void Setup();

	void Update(float deltaTime);
	void Draw() const;
	nlohmann::json Save() const;
	void Reset() const;

private:
	static void SaveToFile(const nlohmann::json& data);
	void AddElement(const nlohmann::json& data);

	std::vector<HUDElement*> m_pHUDElementVec{};
};