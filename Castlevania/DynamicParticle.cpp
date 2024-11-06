#include "pch.h"
#include "DynamicParticle.h"

void DynamicParticle::Update(float deltaTime)
{
	m_RigidBody.UpdatePhysics(deltaTime);
	CheckCollision();
}

void DynamicParticle::CheckCollision()
{
	m_RigidBody.CollideHard();
	m_RigidBody.CollideSoft();
}