#pragma once
#include "Weapon.h"

class BansheeScream : public Weapon
{
public:
	BansheeScream(const Point2f& pivot, int damage);
	virtual ~BansheeScream() override;

	BansheeScream(const BansheeScream& other) = delete;
	BansheeScream& operator=(const BansheeScream& other) = delete;
	BansheeScream(BansheeScream&& other) noexcept = delete;
	BansheeScream& operator=(BansheeScream&& other) noexcept = delete;

	void Draw() const override;
	void Update(Entity* pOwner, float deltaTime) override; 

private:
	void Setup(const Point2f& pivot);
	Sprite* CreateScreamSprite(const Point2f& pivot, float scale);
	void SetHitBox(const Point2f& pivot);

	Texture* m_pTexture{};
	float m_MinScale{}, m_MaxScale{};
	std::vector<Sprite*> m_pSpriteVec{};
	std::vector<float> m_OpacityVec{};
};