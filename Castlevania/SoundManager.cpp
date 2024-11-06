#include "pch.h"
#include "SoundManager.h"
#include "SoundEffect.h"
#include "SoundTrack.h"
#include "myUtils.h"
#include "SoundStream.h"

SoundManager::SoundManager()
{
	Setup();
}

SoundManager::~SoundManager()
{
	for (const auto& soundSetPair : m_SoundSetMap)
	{
		for (SoundEffect* pSoundEffect : soundSetPair.second)
			delete pSoundEffect;
	}
}

void SoundManager::Setup()
{
	if (!m_SoundSetMap.empty()) return;

	nlohmann::json data{};
	myUtils::ParseJson("./Manager/SoundManager.json", data);

	for (const nlohmann::json& soundObject : data)
	{
		const std::string id{ soundObject["id"] };
		m_SoundMultiplierMap.insert({ id, soundObject["multiplier"] });

		if (soundObject["type"] == "effect")
			LoadSoundSet(soundObject);
		else
			LoadSoundTrack(soundObject);
	}
	UpdateVolume();
}

void SoundManager::LoadSoundSet(const nlohmann::json& data)
{
	const std::string id{ data["id"] };
	SoundSet soundSet{};
	int nrSounds{ 1 };
	bool isLooping{ false };
	if (data.contains("nrSounds"))
		nrSounds = data["nrSounds"];
	if (data.contains("loop"))
		isLooping = data["loop"];

	for (int index{ 1 }; index <= nrSounds; ++index)
	{
		soundSet.push_back(new SoundEffect{ GetSoundPath(data, index), isLooping });
	}
		

	m_SoundSetMap.insert({ id, soundSet });
}

void SoundManager::LoadSoundTrack(const nlohmann::json& data)
{
	SoundTrack soundTrack{};
	const std::string id{ data["id"] };
	const std::string path{ data["path"] };

	for (const nlohmann::json& soundObject : data["tracks"])
		soundTrack.AddSound(path + GetSoundPath(soundObject), soundObject["loop"]);

	m_pSoundTrackMap.insert({ id, std::move(soundTrack) });
}

std::string SoundManager::GetSoundPath(const nlohmann::json& data, int index) const
{
	const std::string id{ data["id"] };
	const std::string path{ std::string{data["path"] } + id };
	const std::string fileType{ data["file"] };
	if (index == 0)
		return path + fileType;
	else
		return path + std::to_string(index) + fileType;
}

void SoundManager::Update()
{
	for (auto& soundTrackPair : m_pSoundTrackMap)
		soundTrackPair.second.Update();
}

bool SoundManager::PlaySound(const std::string& id, int index)
{
	const auto soundTrackIterator{ m_pSoundTrackMap.find(id) };
	if (soundTrackIterator != m_pSoundTrackMap.end())
	{
		soundTrackIterator->second.Play();
		return true;
	}

	const auto soundSetIterator{ m_SoundSetMap.find(id) };
	if (soundSetIterator != m_SoundSetMap.end())
		return PlayEffect(soundSetIterator->second, index);
	return false;
}

void SoundManager::StopSound(const std::string& id)
{
	StopTrack(id);
	StopEffect(id);
}

void SoundManager::StopTrack(const std::string& id)
{
	const auto soundTrackIterator{ m_pSoundTrackMap.find(id) };
	if (soundTrackIterator != m_pSoundTrackMap.end())
		soundTrackIterator->second.Stop();
}

void SoundManager::StopEffect(const std::string& id)
{
	const auto soundSetIterator{ m_SoundSetMap.find(id) };
	if (soundSetIterator != m_SoundSetMap.end())
		for (SoundEffect* pSoundEffect : soundSetIterator->second)
			pSoundEffect->Stop();
}

void SoundManager::StopEffects()
{
	SoundEffect::StopAll();
}

void SoundManager::SetVolume(int percentage)
{
	m_Volume = percentage;
	UpdateVolume();
}

void SoundManager::AddVolume(int amount)
{
	m_Volume += amount;
	m_Volume = std::min(100, m_Volume);
	UpdateVolume();
}

void SoundManager::ReduceVolume(int amount)
{
	m_Volume -= amount;
	m_Volume = std::max(0, m_Volume);
	UpdateVolume();
}

int SoundManager::GetVolume() const
{
	return m_Volume;
}

bool SoundManager::PlayEffect(const SoundSet& soundSet, int index) const
{
	if (index < 0)
		index = myUtils::GenRand(int(soundSet.size()) - 1);

	return soundSet[index]->Play(0);
}

void SoundManager::UpdateVolume()
{
	for (auto& soundTrackPair : m_pSoundTrackMap)
		soundTrackPair.second.SetVolume(int(m_Volume * m_SoundMultiplierMap[soundTrackPair.first]));

	for (const auto& soundSetPair : m_SoundSetMap)
	{
		const float multiplier{ m_SoundMultiplierMap[soundSetPair.first] };
		for (SoundEffect* pSoundEffect : soundSetPair.second)
			pSoundEffect->SetVolume(int(m_Volume * multiplier));
	}
}
