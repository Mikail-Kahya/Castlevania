#pragma once
#include "structs.h"
#include "Vector2f.h"
#include "json_fwd.hpp"
#include <map>

class Texture;
class Enemy;

struct Anim
{
	Anim();
	Anim(const Point2f& startPos, float frameWidth, float frameHeight, int fps, int nrFrames, int cols, int rows, bool loop = true);
	Anim(const Point2f& startPos, float frameWidth, float frameHeight, int fps, int nrFrames, bool loop = true);
	Anim(Texture* pTexture, const Point2f& startPos, int fps, int nrFrames, int cols, int rows, bool loop = true);

	Point2f startPos;
	float frameWidth;
	float frameHeight;
	float frameTime;
	int currentFrame;
	int nrFrames;
	int cols;
	int rows;
	bool loop;
	bool reverse;
};

struct Tile
{
	Tile();
	Tile(Texture* pTexture, const Anim& animation);

	Texture* pTexture;
	Anim animation;
};

struct Stats
{
	Stats();
	Stats(int hp, float stamina, int mana, int exp, int damage, int defense);

	int hp;
	float stamina;
	int mana;
	int exp;
	int damage;
	int defense;
};

struct Spawn
{
	Spawn();
	Spawn(const Point2f& pivot, int type);

	Point2f pivot;
	int type;
};

struct EntityData
{
	EntityData() = default;
	EntityData(const nlohmann::json& data);
	void LoadData(const nlohmann::json& data);

	Stats stats{};
	float width{};
	float height{};
};

struct Part
{
	Part();
	Part(const Rectf& srcRect, const Vector2f& velocity, const Vector2f& offset = Vector2f{});

	Rectf srcRect;
	Vector2f offset;
	Vector2f velocity;
};

struct EasingData
{
	enum class Mode { in, out, alternate };

	EasingData();
	EasingData(float maxTime);

	void Activate(float deltaTime);
	void Reset();

	float GetRatio() const;
	void SetEaseMode(Mode easeMode);

	float maxTime{};
	float delay{};

private:
	void IncreaseTimer(float deltaTime);
	void DecreaseTimer(float deltaTime);
	
	float delayTimer{};
	float timer{};
	Mode mode{ Mode::in };
	bool isIncreasing{ true };
};