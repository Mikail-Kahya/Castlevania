#pragma once
class TriggerBox final
{
public:
	TriggerBox();
	TriggerBox(const Rectf& triggerBox, bool triggerOnce = true);
	~TriggerBox() = default;

	TriggerBox(const TriggerBox& other) = default;
	TriggerBox& operator=(const TriggerBox& other) = default;
	TriggerBox(TriggerBox&& other) noexcept = default;
	TriggerBox& operator=(TriggerBox&& other) noexcept = default;

	void Update();
	bool IsTriggered() const;
	Point2f GetPivot() const;

private:
	Rectf m_TriggerBox{};
	bool m_TriggerOnce{};
	bool m_Triggered{ false };
};