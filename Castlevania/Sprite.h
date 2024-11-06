#pragma once
// First tier class: Sprite interface
// Second tier classes: Derived classes implement draw
// Third tier classes: Concrete classes that derive add the texture
#include "base.h"
class Texture;

class Sprite
{
public:
	virtual ~Sprite() = default;

	Sprite(const Sprite& other) = delete;
	Sprite(Sprite&& other) noexcept = delete;
	Sprite& operator=(const Sprite& other) = delete;
	Sprite& operator=(Sprite&& other) noexcept = delete;

	virtual void Update(float elapsedSec) = 0;
	virtual void Draw() const;

	virtual void SetFlip(bool isFlipped);
	void SetRotation(float angle);
	void SetRotatePivot(bool isRotatingAroundPivot);
	void SetScale(float scale);
	void SetPosition(const Point2f& bottomLeft);
	void SetPivot(const Point2f& pivot);
	void SetCenter(const Point2f& center);

	bool IsFlipped() const;
	float GetRotation() const;
	float GetScale() const;
	float GetWidth() const;
	float GetHeight() const;
	Point2f GetPosition() const;

protected:
	Sprite(const Texture* pTexture, const Point2f& bottomLeft, float scale);
	void Translate() const;
	void Rotate() const;
	void Scale() const;

	const Texture* m_pTexture{ nullptr };
	Rectf m_DstRect{};
	Rectf m_SrcRect{};
	float m_Angle{};
	float m_Scale{};
	bool m_IsFlipped{};
	bool m_IsRotatingAroundPivot{ false };
};