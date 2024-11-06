#include "myStructs.h"
#include "myUtils.h"
#include "Texture.h"

Anim::Anim(const Point2f& startPos, float frameWidth, float frameHeight, int fps, int nrFrames, int cols, int rows, bool loop)
	: startPos{ startPos }
	, frameWidth{ frameWidth }
	, frameHeight{ frameHeight }
	, frameTime{ 1.0f / float(fps) }
	, currentFrame{ 0 }
	, nrFrames{ nrFrames }
	, cols{ cols }
	, rows{ rows }
	, loop{ loop }
	, reverse{ false }
{
}

Anim::Anim(const Point2f& startPos, float frameWidth, float frameHeight, int fps, int nrFrames, bool loop)
	: Anim(startPos, frameWidth, frameHeight, fps, nrFrames, nrFrames, 1, loop)
{
}

Anim::Anim(Texture* pTexture, const Point2f& startPos, int fps, int nrFrames, int cols, int rows, bool loop)
	: Anim( startPos, 0.0f, 0.0f, fps, nrFrames, cols, rows, loop)
{
	frameWidth = pTexture->GetWidth() / float(cols);
	frameHeight = pTexture->GetHeight() / float(rows);
}

Anim::Anim()
	: Anim(Point2f{}, 0, 0, 0, 0, 0, 0, 0)
{
}

Tile::Tile()
	: Tile(nullptr, Anim{})
{
}

Tile::Tile(Texture* pTexture, const Anim& animation)
	: pTexture{ pTexture }, animation{ animation }
{
}

Stats::Stats()
	: Stats(0,0,0,0,0,0)
{
}

Stats::Stats(int hp, float stamina, int mana, int exp, int damage, int defense)
	: hp{ hp }
	, stamina{ stamina }
	, mana{ mana }
	, exp{ exp }
	, damage{ damage }
	, defense{ defense }
{
}

Spawn::Spawn()
	: Spawn(Point2f{}, 0)
{
}

Spawn::Spawn(const Point2f& pivot, int type)
	: pivot{ pivot }, type{ type }
{
}

EntityData::EntityData(const nlohmann::json& data)
	: stats{ Stats{ data["hp"], 0, 0, data["exp"], data["damage"], data["defense"] } }
	, width{ data["width"] }
	, height{ data["height"] }
{
}

void EntityData::LoadData(const nlohmann::json& data)
{
	stats = Stats{ data["hp"], 0, 0, data["exp"], data["damage"], data["defense"]};
	width = data["width"];
	height = data["height"];
}

Part::Part()
	: Part(Rectf{}, Vector2f{}, Vector2f{})
{
}

Part::Part(const Rectf& srcRect, const Vector2f& velocity, const Vector2f& offset)
	: srcRect{ srcRect }
	, offset{ offset }
	, velocity{ velocity }
{
}

EasingData::EasingData()
	: EasingData(0)
{
}

EasingData::EasingData(float maxTime)
	: maxTime{ maxTime }
{
}

void EasingData::Activate(float deltaTime)
{
	delayTimer += deltaTime;
	if (delayTimer < delay) return;

	switch (mode)
	{
	case Mode::in:
		IncreaseTimer(deltaTime);
		break;
	case Mode::out:
		DecreaseTimer(deltaTime);
		break;
	case Mode::alternate:
		if (isIncreasing)
			IncreaseTimer(deltaTime);
		else
			DecreaseTimer(deltaTime);
		break;
	}
}

void EasingData::Reset()
{
	delayTimer = 0;
	timer = 0;
}

float EasingData::GetRatio() const
{
	return std::min(timer / maxTime, 1.0f);
}

void EasingData::SetEaseMode(Mode easeMode)
{
	mode = easeMode;
}

void EasingData::IncreaseTimer(float deltaTime)
{
	const float epsilon{ 0.05f };
	timer = std::min(timer + deltaTime, maxTime);
	isIncreasing = (maxTime - timer) > epsilon;
}

void EasingData::DecreaseTimer(float deltaTime)
{
	const float epsilon{ 0.05f };
	timer = std::max(timer - deltaTime, 0.0f);
	isIncreasing = timer <= epsilon;
}
