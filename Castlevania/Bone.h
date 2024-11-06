#pragma once
#include "ThrowableWeapon.h"

class Bone : public ThrowableWeapon
{
public:
	Bone(const Point2f& from, const Point2f& to, int damage);
	virtual ~Bone() override;

	Bone(const Bone& other) = delete;
	Bone& operator=(const Bone& other) = delete;
	Bone(Bone&& other) noexcept = delete;
	Bone& operator=(Bone&& other) noexcept = delete;

	void Draw() const override;
	void Update(Entity* pOwner, float deltaTime) override;
	void OnHit() override;

private:
	void Rotate(float deltaTime) const;

	BasicSprite* m_pSprite{ nullptr };
};