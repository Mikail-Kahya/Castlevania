// Create a state machine
// Entity switches states
// Abstract class "EntityState" creates the interface to the state machine

// Levels:
//	1. EntityState class
//	2. Abstract object such as PlayerState
//	3. Derived classes are major states such as "InAir", "OnGround", etc...
//	4. Derived classes implementing logic and behaviour of a state

#pragma once
class Entity;

class EntityState
{
public:
	EntityState() = default;
	virtual ~EntityState() = default;

	EntityState(const EntityState& other) = delete;
	EntityState& operator=(const EntityState& other) = delete;
	EntityState(EntityState&& other) noexcept = delete;
	EntityState& operator=(EntityState&& other) noexcept = delete;

	virtual void Update(Entity* pEntity, float deltaTime) = 0;
	virtual EntityState* GetNextState(Entity* pEntity, float deltaTime) = 0;

protected:
	const Stats& GetStats(Entity* pEntity) const;
	const Vector2f& GetVelocity(Entity* pEntity) const;
	float GetAnimationTime(Entity* pEntity) const;
	int GetDirection(Entity* pEntity) const;
	float GetAnimationWidth(Entity* pEntity) const;
	float GetAnimationHeight(Entity* pEntity) const;
	bool IsLastFrame(Entity* pEntity) const;
	bool IsHurt(Entity* pEntity) const;
	bool IsDead(Entity* pEntity) const;
	bool IsFlipped(Entity* pEntity) const;
	bool IsReversed(Entity* pEntity) const;
	bool IsGrounded(Entity* pEntity) const;

	void SetVelocityX(Entity* pEntity, float x);
	void SetVelocityY(Entity* pEntity, float y);
	void SetVelocity(Entity* pEntity, const Vector2f& velocity);
	void SetHurtWidth(Entity* pEntity, float width);
	void SetHurtHeight(Entity* pEntity, float height);
	void SetActiveAnimation(Entity* pEntity, const std::string& id);
	void SetFlip(Entity* pEntity, bool isFlipped);
	void SetReverse(Entity* pEntity, bool isReversed);
	void SetSpritePivot(Entity* pEntity, const Point2f& pivot);
	void SetRigidPivot(Entity* pEntity, const Point2f& pivot);
	void SetImmune(Entity* pEntity, float immuneTime);
};