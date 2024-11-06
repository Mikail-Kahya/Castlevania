#include "pch.h"
#include "GameObject.h"
int GameObject::NR_GAMEOBJECTS{ 0 };

GameObject::GameObject()
{
	++NR_GAMEOBJECTS;
}

GameObject::~GameObject()
{
	--NR_GAMEOBJECTS;
}
