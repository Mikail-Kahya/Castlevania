#pragma once
// PickUps are the base class
// PickUps get a sprite set to draw => Derived classes also hold a pointer to the same object for updating
// PickUp has no authority over deletion

#include "GameObject.h"
#include "Level.h"
#include "RigidBody.h"
#include "TextureManager.h"

class PickUp : public GameObject
{
public:
	PickUp() = default;
	virtual ~PickUp() override;

	PickUp(const PickUp& other) = delete;
	PickUp& operator=(const PickUp& other) = delete;
	PickUp(PickUp&& other) noexcept = delete;
	PickUp& operator=(PickUp&& other) noexcept = delete;

	void Draw() const override;
	void Update(float deltaTime) override;
	virtual bool Collect();

protected:
	virtual void UpdateRigidBody(float deltaTime);
	void SetSprite(Sprite* pSprite);

	RigidBody m_RigidBody{};

private:
	Sprite* m_pSprite{ nullptr };
};

