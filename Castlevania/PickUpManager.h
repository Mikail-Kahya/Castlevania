#pragma once
class PickUp;
class Player;

class PickUpManager final
{
public:
	PickUpManager() = default;
	~PickUpManager();

	PickUpManager(const PickUpManager& other) = delete;
	PickUpManager& operator=(const PickUpManager& other) = delete;
	PickUpManager(PickUpManager&& other) noexcept = delete;
	PickUpManager& operator=(PickUpManager&& other) noexcept = delete;

	void Draw() const;
	void Update(float deltaTime);

	void AddPickUp(PickUp* pPickUp);

private:
	void ClearVector();
	void DeletePickUp(int index);

	std::vector<PickUp*> m_pPickUpVec{};
};

