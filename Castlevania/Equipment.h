#pragma once
class ThrowableWeapon;
class Weapon;
class Entity;
class EntityState;

class Equipment final
{
public:

	Equipment() = default;
	~Equipment();

	Equipment(const Equipment& other) = delete;
	Equipment& operator=(const Equipment& other) = delete;
	Equipment(Equipment&& other) noexcept = delete;
	Equipment& operator=(Equipment&& other) noexcept = delete;

	void Draw() const;
	void Update(Entity* pEntity, float deltaTime);
	void ThrowWeapon(ThrowableWeapon* pThrowableWeapon);
	bool AddWeapon(const std::string& id, Weapon* pWeapon);
	bool DeleteWeapon(const std::string& id);

	const std::vector<ThrowableWeapon*>& GetThrowableWeapons() const;
	Weapon* GetActiveWeapon() const;
	bool SetActiveWeapon(const std::string& id, float delay);
	void DisableActiveWeapon();

private:
	void CheckSelfDisable();
	bool DeleteWeapon(const std::map<std::string, Weapon*>::iterator& iterator);

	std::map<std::string, Weapon*> m_pWeaponMap{};
	std::vector<ThrowableWeapon*> m_pThrowableWeaponVec{};
	Weapon* m_pActiveWeapon{ nullptr };
};