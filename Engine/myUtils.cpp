#include "base.h"
#include "myUtils.h"
#include <fstream>

#pragma region Generate
	int myUtils::GenRand(int max)
	{
		return GenRand(0, max);
	}
	int myUtils::GenRand(int min, int max)
	{
		return rand() % (max - min + 1) + min;
	}

	float myUtils::GenRand(float max)
	{
		return GenRand(0.f, max);
	}
	float myUtils::GenRand(float min, float max)
	{
		const float random{ (float)rand() / (float)RAND_MAX };
		const float range{ max - min };
		return min + random * range;
	}

	int myUtils::GetRandDirection()
	{
		int direction{ GenRand(-1, 1) };
		if (direction == 0)
			direction = 1;
		return direction;
	}

	Point2f myUtils::GetRandPointInRect(const Rectf& r)
	{
		const float minX{ r.left }, maxX{ r.left + r.width };
		const float minY{ r.bottom }, maxY{ r.bottom + r.height };

		return Point2f{ GenRand(minX, maxX), GenRand(minY, maxY) };
	}

	Point2f myUtils::GetRandPointOnLine(const Point2f& start, const Point2f& end)
	{
		return GetRandPointOnLine(start, Vector2f{ start, end });
	}
	Point2f myUtils::GetRandPointOnLine(const Point2f& origin, const Vector2f& line)
	{

		const float randLength{ GenRand(line.Length()) };
		const Vector2f translate{ line.Normalized() * randLength };

		return Point2f{ origin + translate };
	}

Color4f myUtils::RGBToColor4f(int r, int g, int b, int a)
	{
		const float maxRGB{ 255 };
		return Color4f{ r / maxRGB, g / maxRGB, b / maxRGB, a / maxRGB };
	}
	Color4f myUtils::HexToColor4f(int hexCode)
	{
		const float r{ float(hexCode >> 4 & 0xFF) / 0xFF };
		const float g{ float(hexCode >> 8 & 0xFF) / 0xFF };
		const float b{ float(hexCode >> 12 & 0xFF) / 0xFF };
		return Color4f{ r, g, b, 1.0f };
	}

	float myUtils::CalcSineWave(float x, float amplitude, float periodLength, float intercept, float phase)
	{
		const float periodicity{ 2 * float(M_PI) / periodLength };
		return amplitude * sinf(periodicity * x + phase) + intercept;
	}

#pragma endregion Generate

#pragma region Collision
	bool myUtils::IsCircleInRect(const Rectf& boundingBox, const Circlef& shape)
	{
		const float
			shapeBottom{ shape.center.y - shape.radius },
			shapeTop{ shape.center.y + shape.radius },
			shapeLeft{ shape.center.x - shape.radius },
			shapeRight{ shape.center.x + shape.radius };


		const float
			boundingBottom{ boundingBox.bottom },
			boundingTop{ boundingBox.bottom + boundingBox.height },
			boundingLeft{ boundingBox.left },
			boundingRight{ boundingBox.left + boundingBox.width };

		if (boundingBottom > shapeBottom)
			return false;

		if (boundingTop < shapeTop)
			return false;

		if (boundingLeft > shapeLeft)
			return false;

		if (boundingRight < shapeRight)
			return false;

		return true;
	}
#pragma endregion Collision

	bool myUtils::ParseJson(const std::string& path, nlohmann::json& data)
	{
		std::ifstream file(path);

		// file is not found
		if (!file)
		{
			std::cout << path << " not found\n";
			file.close();
			return false;
		}

		// check whether file is valid json
		if (nlohmann::json::accept(file))
		{
			// reload file due to issue with exceptions
			file.clear();
			file.seekg(0);

			// parse
			data = nlohmann::json::parse(file, nullptr, false, false);

			file.close();
			return true;
		}
		else
		{
			std::cout << path << " is not valid JSON data\n";
			file.close();
			return false;
		}
	}

	Anim myUtils::CreateAnim(const nlohmann::json& data)
	{
		const Point2f pos{ data["x"], data["y"] };
		const float width{ data["frameWidth"] };
		const float height{ data["frameHeight"] };
		const int nrFrames{ data["nrFrames"] };
		const int nrCols{ data["nrCols"] };
		const int nrRows{ data["nrRows"] };
		const int fps{ data["fps"] };
		const bool isLooping{ data["isLooping"] };
		return Anim{ pos, width, height, fps, nrFrames, nrCols, nrRows, isLooping };
	}

	Part myUtils::CreatePart(const nlohmann::json& data)
	{
		const Rectf srcRect{ data["src"]["x"], data["src"]["y"],
							data["src"]["w"], data["src"]["h"] };
		const Vector2f velocity{ data["velocity"]["x"], data["velocity"]["y"] };

		Vector2f offset{};

		if (data.contains("offset"))
		{
			offset.x = data["offset"]["x"];
			offset.y = data["offset"]["y"];
		}

		return Part{ srcRect, velocity, offset };
	}

std::vector<Part> myUtils::CreateParts(const std::string& path)
{
	nlohmann::json data{};
	ParseJson(path, data);

	std::vector<Part> partVec{};
	for (const auto& object : data)
		partVec.push_back(CreatePart(object));

	return partVec;
}

Point2f myUtils::Lerp(const Point2f& from, const Point2f& to, float ratio)
{
	return Point2f{ Lerp(from.x, to.x, ratio), Lerp(from.y, to.y, ratio) };
}

Vector2f myUtils::Lerp(const Vector2f& from, const Vector2f& to, float ratio)
{
	return Vector2f{ Lerp(from.x, to.x, ratio), Lerp(from.y, to.y, ratio) };
}

float myUtils::Lerp(float from, float to, float ratio)
{
	return (1 - ratio) * from + ratio * to;
}
