#pragma once
class LevelCalculator
{
public:
	LevelCalculator(int exp = 0);

	bool operator()(int exp);
	int operator()() const;

private:
	int GetLevel();
	int GetExpForLevel(int level);

	static constexpr int BASE{ 30 };
	static constexpr int GROWTH{ 20 };

	int m_Exp{};
	int m_Level{ 0 };
};