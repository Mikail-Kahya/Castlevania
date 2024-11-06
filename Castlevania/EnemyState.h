#pragma once
#include "EntityState.h"
#include "Vector2f.h"

class EnemyState : public EntityState
{
public:
	EnemyState() = default;
	virtual ~EnemyState() = default;

	EnemyState(const EnemyState& other) = delete;
	EnemyState& operator=(const EnemyState& other) = delete;
	EnemyState(EnemyState&& other) noexcept = delete;
	EnemyState& operator=(EnemyState&& other) noexcept = delete;

	virtual void Update(Entity* pEntity, float deltaTime) = 0;
	virtual EntityState* GetNextState(Entity* pEntity, float deltaTime) = 0;

protected:
	Vector2f GetPlayerDistance(Entity* pEntity) const;
	void FacePlayer(Entity* pEntity);
	void SetDelete(Entity* pEntity, bool allowDelete);
	void SetAllowHurt(Entity* pEntity, bool allowHurt);
};