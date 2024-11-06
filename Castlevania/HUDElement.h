#pragma once
#include "GUIElement.h"

class HUDElement
{
public:
	HUDElement() = default;
	virtual ~HUDElement() = default;

	HUDElement(const HUDElement& other) = delete;
	HUDElement& operator=(const HUDElement& other) = delete;
	HUDElement(HUDElement&& other) noexcept = delete;
	HUDElement& operator=(HUDElement&& other) noexcept = delete;

	virtual void Draw() const = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Save(nlohmann::json& data) = 0;
	virtual void Reset() = 0;
};