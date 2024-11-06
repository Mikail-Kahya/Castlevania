#pragma once
class SoundEffect;
class SoundTrack;

using SoundSet = std::vector<SoundEffect*>;

class SoundManager final
{
public:
	friend SoundManager& GetSoundManager();

	~SoundManager();

	SoundManager(const SoundManager& other) = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) noexcept = delete;
	SoundManager& operator=(SoundManager&& other) noexcept = delete;

	void Update();

	bool PlaySound(const std::string& id, int index = -1);
	void StopSound(const std::string& id);
	void StopEffects();

	void SetVolume(int percentage);
	void AddVolume(int amount);
	void ReduceVolume(int amount);

	int GetVolume() const;

private:
	SoundManager();

	void Setup();
	void LoadSoundSet(const nlohmann::json& data);
	void LoadSoundTrack(const nlohmann::json& data);
	std::string GetSoundPath(const nlohmann::json& data, int index = 0) const;

	void StopTrack(const std::string& id);
	void StopEffect(const std::string& id);
	bool PlayEffect(const SoundSet& soundSet, int index) const;
	void UpdateVolume();

	std::map<std::string, SoundSet> m_SoundSetMap{};
	std::map<std::string, SoundTrack> m_pSoundTrackMap{};
	std::map<std::string, float> m_SoundMultiplierMap{};
	int m_Volume{ 50 };

};

inline SoundManager& GetSoundManager()
{
	static SoundManager soundManager{};
	return soundManager;
}