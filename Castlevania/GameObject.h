#pragma once

class Level;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(float elapsedSec) = 0;
	virtual void Draw() const = 0;
	
	static int NR_GAMEOBJECTS;
};

