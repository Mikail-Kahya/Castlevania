#pragma once
#include "Enemy.h"
#include "SkeletonRangedState.h"
class Bone;

class SkeletonRanged : public Enemy
{
public:
	SkeletonRanged(const Point2f& pivot, const EntityData& entityData);
	virtual ~SkeletonRanged() override;

	SkeletonRanged(const SkeletonRanged& other) = delete;
	SkeletonRanged& operator=(const SkeletonRanged& other) = delete;
	SkeletonRanged(SkeletonRanged&& other) noexcept = delete;
	SkeletonRanged& operator=(SkeletonRanged&& other) noexcept = delete;

	void Update(float deltaTime) override;
	void Draw() const override;
	bool Hurt(const Rectf& hitBox, int damage) override;

private:
	friend class SkeletonRangedState::Base;

	static void LoadStatics();
	bool IsAttacking() const;
	void SpawnParts() const;

	static std::vector<Part> m_DefaultPartVec;
	Bone* m_pBone{ nullptr };
};