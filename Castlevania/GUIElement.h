// GUIElement is the base class for every small element on the ui
	// Examples are hp bars, number counters, buttons, etc...
// built out of several levels
	// 1. base class (abstract)
	// 2. interacting (abstract), stat (abstract), overlay
	// 3. implementing general class
	// 4. possible specific use cases

#pragma once

class GUIElement
{
public:
	GUIElement() = default;
	virtual ~GUIElement() = default;

	GUIElement(const GUIElement& other) = delete;
	GUIElement& operator=(const GUIElement& other) = delete;
	GUIElement(GUIElement&& other) noexcept = delete;
	GUIElement& operator=(GUIElement&& other) noexcept = delete;

	virtual void Draw() const = 0;
	virtual void Update(float deltaTime) = 0;
};