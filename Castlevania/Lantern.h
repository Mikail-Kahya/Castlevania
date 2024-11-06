#pragma once
#include "Destructable.h"
class Level;

class Lantern : public Destructable
{
public:
	Lantern(const Point2f& pivot);
	virtual ~Lantern() = default;

	Lantern(const Lantern& other) = delete;
	Lantern& operator=(const Lantern& other) = delete;
	Lantern(Lantern&& other) noexcept = delete;
	Lantern& operator=(Lantern&& other) noexcept = delete;

	void Update(float deltaTime) override;
	PickUp* SpawnPickUp() const override;

private:
	void LoadStatics();
	void Setup(const Point2f& pivot);
	bool Hurt(const Rectf& hitBox) override;
	void SpawnParts();

	static const Rectf m_DefaultHurtBox;
	static std::vector<Part> m_DefaultPartVec;
};