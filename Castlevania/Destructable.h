#pragma once
#include "GameObject.h"

class PickUp;
class EntityState;
class Level;

class Destructable : public GameObject
{
public:
	Destructable() = default;
	virtual ~Destructable() override;

	Destructable(const Destructable& other) = delete;
	Destructable& operator=(const Destructable& other) = delete;
	Destructable(Destructable&& other) noexcept = delete;
	Destructable& operator=(Destructable&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;
	virtual bool Hurt(const Rectf& hitBox);
	virtual PickUp* SpawnPickUp() const = 0;
	bool AllowDelete() const;

protected:
	void SetRigidPivot(const Point2f& pivot);
	void SetDelete(bool canDelete);

	Sprite* m_pSprite{ nullptr };
	Rectf m_HurtBox{};
	bool m_AllowDelete{ false };

private:
	bool m_Hit{ false };
};