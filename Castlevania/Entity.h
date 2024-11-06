#pragma once
#include "GameObject.h"
#include "RigidBody.h"

class BloodSplatter;
class EntityState;
class Level;

class Entity : public GameObject
{
public:
	Entity() = default;
	virtual ~Entity() override;

	Entity(const Entity& other) = delete;
	Entity& operator=(const Entity& other) = delete;
	Entity(Entity&& other) noexcept = delete;
	Entity& operator=(Entity&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;
	virtual bool Hurt(const Rectf& hitBox, int damage);

	Rectf GetHurtBox() const;
	const Point2f& GetPivot() const;

protected:
	virtual void Setup(const std::string& id, const Point2f& pivot, const EntityData& entityData);

	virtual void UpdateState(float deltaTime);
	virtual void UpdateSprite(float deltaTime);
	virtual void UpdateRigidBody(float deltaTime);
	void SprayBlood(const Rectf& hitBox) const;
	void SprayBlood(const Rectf& hitBox, const Point2f& bottomLeft) const;
	void SpawnDamage(int damage, const Color4f& color);

	virtual void SetState(EntityState* pState);
	void SetImmuneTime(float immuneTime);
	virtual EntityState* GetState() const;
	bool IsDead() const;
	bool IsHurt() const;
	bool IsFlickering() const;

	RigidBody m_RigidBody{};
	Stats m_Stats{};
	Avatar* m_pSprite{ nullptr };
	bool m_IsFlickering{ false };

private:
	friend class EntityState;
	friend class Weapon;

	void UpdateFlicker(float deltaTime);

	float m_ImmuneTime{ 1 };
	float m_ImmuneTimer{};
	float m_FlickerTimer{};
	EntityState* m_pState{ nullptr };
};