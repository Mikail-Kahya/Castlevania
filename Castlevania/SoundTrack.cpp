#include "pch.h"
#include "SoundTrack.h"
#include "SoundStream.h"

SoundTrack::~SoundTrack()
{
	DeleteSoundTrack();
}

SoundTrack::SoundTrack(const SoundTrack& other)
	: m_SoundStreamLoopVec{ other.m_SoundStreamLoopVec }
	, m_SoundIndex{ other.m_SoundIndex }
	, m_IsPlaying{ other.m_IsPlaying }
{
	CopySoundTrack(other);
}

SoundTrack& SoundTrack::operator=(const SoundTrack& other)
{
	DeleteSoundTrack();
	m_SoundStreamLoopVec = other.m_SoundStreamLoopVec;
	m_SoundIndex = other.m_SoundIndex;
	m_IsPlaying = other.m_IsPlaying;
	CopySoundTrack(other);

	return *this;
}

SoundTrack::SoundTrack(SoundTrack&& other) noexcept
	: m_pSoundStreamVec{ std::move(other.m_pSoundStreamVec) }
	, m_SoundStreamLoopVec{ std::move(other.m_SoundStreamLoopVec) }
	, m_SoundIndex{ other.m_SoundIndex }
	, m_IsPlaying{ other.m_IsPlaying }
{
}

SoundTrack& SoundTrack::operator=(SoundTrack&& other) noexcept
{
	DeleteSoundTrack();
	m_pSoundStreamVec = std::move(other.m_pSoundStreamVec);
	m_SoundStreamLoopVec = std::move(other.m_SoundStreamLoopVec);
	m_SoundIndex = other.m_SoundIndex;
	m_IsPlaying = other.m_IsPlaying;

	return *this;
}

void SoundTrack::Update()
{
	if (!m_IsPlaying) return;
	if (!m_pSoundStreamVec[m_SoundIndex]->IsPlaying())
		NextSound();
}

void SoundTrack::Stop()
{
	m_SoundIndex = 0;
	Pause();
}

void SoundTrack::Play()
{
	m_SoundIndex = 0;
	Resume();
	m_pSoundStreamVec[m_SoundIndex]->Play(m_SoundStreamLoopVec[m_SoundIndex]);
}

void SoundTrack::Pause()
{
	m_IsPlaying = false;
}

void SoundTrack::Resume()
{
	m_IsPlaying = true;
}

void SoundTrack::Skip()
{
	NextSound();
}

void SoundTrack::AddSound(const std::string& path, bool isLooping)
{
	m_pSoundStreamVec.push_back(new SoundStream{ path });
	m_SoundStreamLoopVec.push_back(isLooping);
}

void SoundTrack::SetVolume(int volume)
{
	for (SoundStream* pSoundStream : m_pSoundStreamVec)
		pSoundStream->SetVolume(volume);
}

bool SoundTrack::IsPlaying() const
{
	return m_IsPlaying;
}

void SoundTrack::NextSound()
{
	m_pSoundStreamVec[m_SoundIndex]->Pause();
	m_SoundIndex = ++m_SoundIndex % m_pSoundStreamVec.size();
	m_pSoundStreamVec[m_SoundIndex]->Play(m_SoundStreamLoopVec[m_SoundIndex]);
}

void SoundTrack::DeleteSoundTrack()
{
	for (SoundStream* pSoundStream : m_pSoundStreamVec)
		delete pSoundStream;
	m_pSoundStreamVec.clear();
}

void SoundTrack::CopySoundTrack(const SoundTrack& other)
{
	for (SoundStream* pSoundStream : other.m_pSoundStreamVec)
		m_pSoundStreamVec.push_back(pSoundStream->Clone());
}