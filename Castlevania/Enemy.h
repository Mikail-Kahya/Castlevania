#pragma once
#include "Entity.h"
class EnemyState;
class PickUp;

class  Enemy: public Entity
{
public:
	Enemy();
	virtual ~Enemy() = default;

	Enemy(const Enemy& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;
	Enemy(Enemy&& other) noexcept = delete;
	Enemy& operator=(Enemy&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;
	bool Hurt(const Rectf& hitBox, int damage) override;

	bool AllowDelete() const;
	int GetExp() const;

protected:
	void DrawFlicker() const;

	bool m_AllowHurt{ true };
	bool m_AllowDelete{ false };

private:
	friend class EnemyState;
	friend class EnemyManager;
};