#pragma once
// Base class weapon draws the sprite provided by the derived classes
// Draw and update are virtual (some weapons are a simpleSprites and others animated)

class Entity;
class WeaponState;
class EntityState;

class Weapon
{
public:
	virtual ~Weapon() = default;

	Weapon(const Weapon& other) = delete;
	Weapon& operator=(const Weapon& other) = delete;
	Weapon(Weapon&& other) noexcept = delete;
	Weapon& operator=(Weapon&& other) noexcept = delete;

	virtual void Draw() const;
	virtual void Update(Entity* pOwner, float deltaTime);
	virtual bool Use(float delay);
	void Disable();

	const Rectf& GetHitbox() const;
	int GetDamage() const;
	bool IsActive() const;

	void SetBottomLeft(const Point2f& bottomLeft);

protected:
	Weapon(int damage);

	bool IsFlipped(Entity* pOwner);

	Rectf m_Hitbox{};
	const int m_Damage{};
	bool m_IsActive{ false };
	float m_UseDelayTimer{};
};