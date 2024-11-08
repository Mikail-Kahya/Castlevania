#pragma once
#include <string>
class Mix_Chunk;
class SoundEffect final
{
public:
	explicit SoundEffect( const std::string& path, bool isLooping = false );
	~SoundEffect( );
	SoundEffect(const SoundEffect& other) = delete;
	SoundEffect& operator=(const SoundEffect& rhs) = delete;
	SoundEffect( SoundEffect&& other) = delete;
	SoundEffect& operator=( SoundEffect&& rhs) = delete;

	bool IsLoaded( ) const;
	bool Play( int loops );
	void Stop();
	void SetVolume( const int value ); 
	int GetVolume( ) const;
	static void StopAll( );
	static void PauseAll( );
	static void ResumeAll( );

private:
	Mix_Chunk* m_pMixChunk;
	const bool m_IsLooping{};
	int m_Channel{};
};
