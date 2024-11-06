#pragma once
#include "Weapon.h"
class Entity;
class EntityState;

class PlayerWeapon : public Weapon
{
public:
	PlayerWeapon(int damage);
	virtual ~PlayerWeapon() override;

	PlayerWeapon(const PlayerWeapon& other) = delete;
	PlayerWeapon& operator=(const PlayerWeapon& other) = delete;
	PlayerWeapon(PlayerWeapon&& other) noexcept = delete;
	PlayerWeapon& operator=(PlayerWeapon&& other) noexcept = delete;

	void Draw() const override;
	void Update(Entity* pOwner, float deltaTime) override;

protected:
	enum class State { standing, crouched, air };

	void SetSprite(BasicSprite* pSprite);
	void SetOffset(const Point2f& offset, State offsetState);

private:
	const Point2f& GetOffset() const;

	Point2f m_OffsetArr[3]{};

	BasicSprite* m_pSprite{ nullptr };
};