#pragma once
class SoundStream;

class SoundTrack final
{
public:
	SoundTrack() = default;
	~SoundTrack();

	SoundTrack(const SoundTrack& other);
	SoundTrack& operator=(const SoundTrack& other);
	SoundTrack(SoundTrack&& other) noexcept;
	SoundTrack& operator=(SoundTrack&& other) noexcept;

	void Update();
	void Stop();
	void Play();
	void Pause();
	void Resume();
	void Skip();
	void AddSound(const std::string& path, bool isLooping = false);
	void SetVolume(int volume);
	bool IsPlaying() const;

private:
	void NextSound();
	void DeleteSoundTrack();
	void CopySoundTrack(const SoundTrack& other);

	std::vector<SoundStream*> m_pSoundStreamVec{};
	std::vector<bool> m_SoundStreamLoopVec{};
	unsigned int m_SoundIndex{};
	bool m_IsPlaying{ false };
};
