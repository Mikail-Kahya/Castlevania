#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(const Texture* pTexture, const Point2f& bottomLeft, float scale)
	: m_pTexture{ pTexture }
	, m_Scale{ scale }
{
	m_DstRect = Rectf{ bottomLeft, pTexture->GetWidth() * scale, pTexture->GetWidth() * scale };
}

void Sprite::Draw() const
{
	glPushMatrix();

	Translate();
	Rotate();
	Scale();

	m_pTexture->Draw(Point2f{}, m_SrcRect);

	glPopMatrix();
}

void Sprite::SetFlip(bool isFlipped)
{
	m_IsFlipped = isFlipped;
}

void Sprite::SetRotation(float angle)
{
	m_Angle = angle;
}

void Sprite::SetRotatePivot(bool isRotatingAroundPivot)
{
	m_IsRotatingAroundPivot = isRotatingAroundPivot;
}

void Sprite::SetScale(float scale)
{
	m_Scale = scale;
}

void Sprite::SetPosition(const Point2f& bottomLeft)
{
	m_DstRect.left = bottomLeft.x;
	m_DstRect.bottom = bottomLeft.y;
}

void Sprite::SetPivot(const Point2f& pivot)
{
	m_DstRect.left = pivot.x - m_DstRect.width / 2;
	m_DstRect.bottom = pivot.y;
}

void Sprite::SetCenter(const Point2f& center)
{
	m_DstRect.left = center.x - m_DstRect.width / 2;
	m_DstRect.bottom = center.y - m_DstRect.height / 2;
}

float Sprite::GetRotation() const
{
	return m_Angle;
}

float Sprite::GetScale() const
{
	return m_Scale;
}

float Sprite::GetWidth() const
{
	return m_DstRect.width;
}

float Sprite::GetHeight() const
{
	return m_DstRect.height;
}

Point2f Sprite::GetPosition() const
{
	return Point2f{ m_DstRect.left, m_DstRect.bottom };
}

bool Sprite::IsFlipped() const
{
	return m_IsFlipped;
}

void Sprite::Translate() const
{
	glTranslatef(m_DstRect.left, m_DstRect.bottom, 0.0f);
}

void Sprite::Rotate() const
{
	const float margin{ 0.05f };
	if (abs(m_Angle) > margin)
	{
		const float halfWidth{ m_DstRect.width / 2 };
		const float halfHeight{ m_DstRect.height / 2 };

		if (m_IsRotatingAroundPivot)
		{
			glTranslatef(halfWidth, 0, 0.0f);
			glRotatef(m_Angle, 0, 0, 1);
			glTranslatef(-halfWidth, 0, 0.0f);
		}
		else
		{
			glTranslatef(halfWidth, halfHeight, 0.0f);
			glRotatef(m_Angle, 0, 0, 1);
			glTranslatef(-halfWidth, -halfHeight, 0.0f);
		}
	}
}

void Sprite::Scale() const
{
	if (m_IsFlipped)
	{
		glTranslatef(m_DstRect.width, 0.0f, 0.0f);
		glScalef(-m_Scale, m_Scale, 1.0f);
	}
	else
	{
		glScalef(m_Scale, m_Scale, 1.0f);
	}
}