#pragma once
#include "myStructs.h"
#include <json_fwd.hpp>

namespace myUtils
{
#pragma region Generate
	int GenRand(int max);
	int GenRand(int min, int max);
	float GenRand(float max);
	float GenRand(float min, float max);
	int GetRandDirection();
	Point2f GetRandPointInRect(const Rectf& r);
	Point2f GetRandPointOnLine(const Point2f& start, const Point2f& end);
	Point2f GetRandPointOnLine(const Point2f& origin, const Vector2f& line);

	Color4f RGBToColor4f(int r, int g, int b, int a = 255);
	Color4f HexToColor4f(int hexCode);
#pragma endregion Generate
	float CalcSineWave(float x, float amplitude, float periodLength, float intercept = 0, float phase = 0);

#pragma region Collision
	bool IsCircleInRect(const Rectf& boundingBox, const Circlef& shape);
#pragma endregion Collision

	bool ParseJson(const std::string& path, nlohmann::json& data);
	Anim CreateAnim(const nlohmann::json& data);
	Part CreatePart(const nlohmann::json& data);
	std::vector<Part> CreateParts(const std::string& path);

	Point2f Lerp(const Point2f& from, const Point2f& to, float ratio);
	Vector2f Lerp(const Vector2f& from, const Vector2f& to, float ratio);
	float Lerp(float from, float to, float ratio);
}