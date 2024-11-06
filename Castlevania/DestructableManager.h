#pragma once
#include "PickUpManager.h"
class PickUp;
class Destructable;

class DestructableManager final
{
public:
	DestructableManager();
	~DestructableManager();

	DestructableManager(const DestructableManager& other) = delete;
	DestructableManager& operator=(const DestructableManager& other) = delete;
	DestructableManager(DestructableManager&& other) noexcept = delete;
	DestructableManager& operator=(DestructableManager&& other) noexcept = delete;

	void Update(PickUpManager& pickUpManager, float deltaTime);
	void Draw() const;

private:
	void CreateDestructables(const Rectf& bounds, int activeRoom);
	void ClearDestructables();
	void DeleteDestructable(int index);

	nlohmann::json m_Data{};
	std::vector<Destructable*> m_pDestructableVec{};
};

