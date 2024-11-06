#pragma once
#include "HUDElement.h"
#include <map>

class StatBar : public HUDElement
{
public:
	StatBar(const nlohmann::json& data);
	virtual ~StatBar() override;

	StatBar(const StatBar& other) = delete;
	StatBar& operator=(const StatBar& other) = delete;
	StatBar(StatBar&& other) noexcept = delete;
	StatBar& operator=(StatBar&& other) noexcept = delete;

	void Draw() const override;
	void Update(float deltaTime) override;
	void Save(nlohmann::json& data) override {}
	void Reset() override {}

private:
	std::map<std::string, GUIElement*> m_pUIElementMap{};
};