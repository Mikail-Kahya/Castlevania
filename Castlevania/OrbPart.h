#pragma once
#include "FlyingParticle.h"

class OrbPart : public FlyingParticle
{
public:
	OrbPart(const Point2f& bottomLeft, int partIndex);
	virtual ~OrbPart() = default;

	OrbPart(const OrbPart& other) = delete;
	OrbPart& operator=(const OrbPart& other) = delete;
	OrbPart(OrbPart&& other) noexcept = delete;
	OrbPart& operator=(OrbPart&& other) noexcept = delete;

	void Update(float deltaTime) override;
	virtual void Draw() const;
	static size_t GetNrParts();

private:
	static void LoadStatics();

	static std::vector<Part> m_PartVec;

	float m_Opacity{ 1 };
	BasicSprite* m_pSprite{};
};