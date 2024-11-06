#pragma once
#include "Entity.h"
#include "Equipment.h"
#include "LevelCalculator.h"
class EntityState;

class Player : public Entity
{
public:
	virtual ~Player() = default;

	friend Player* GetPlayer();

	void Draw() const override;
	void Update(float deltaTime) override;
	bool Hurt(const Rectf& hitBox, int damage) override;

	Weapon* GetActiveWeapon() const;
	const Stats& GetMaxStats() const;
	const Stats& GetStats() const;
	const Vector2f& GetVelocity() const;
	bool IsCrouched() const;
	bool IsGrounded() const;

	void AllowControl(bool allowControl);
	void AddMana(int mana);
	void AddExp(int exp);
	void Respawn();
	void Reset();
	void HardReset();

private:
	friend class PlayerState;
	friend class MapMechanic;

	Player();

	void Setup();
	void SetupSpawn();
	void SetupStats(const nlohmann::json& data);
	void SetupRigidBody(const nlohmann::json& data);
	void SetupSprite();

	void UpdateSprite(float deltaTime) override;
	void UpdateRigidBody(float deltaTime) override;

	void UpdateLevel();
	void GetDefaultData(nlohmann::json& data);

	bool IsDodging() const;

	Stats m_DefaultStats{};
	Stats m_MaxStats{};
	Equipment m_Equipment{};
	LevelCalculator m_LevelCalculator{};
	bool m_AllowControl{ true };
	bool m_AvoidPlatforms{ false };
	bool m_IsCollidingHard{ false };
};

inline Player* GetPlayer()
{
	static Player* pPlayer{ new Player{} };
	return pPlayer;
}