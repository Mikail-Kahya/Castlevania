#include "base.h"
#include <iostream>
#include "SoundEffect.h"

SoundEffect::SoundEffect( const std::string& path, bool isLooping)
	:m_pMixChunk{ Mix_LoadWAV( path.c_str( ) ) }
	, m_IsLooping{ isLooping }
{
	if ( m_pMixChunk == nullptr )
	{
		const std::string errorMsg = "SoundEffect: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError( );
		std::cerr << errorMsg;
	}
}
SoundEffect::~SoundEffect( )
{
	Mix_FreeChunk( m_pMixChunk );
	m_pMixChunk = nullptr;
}

bool SoundEffect::IsLoaded( ) const
{
	return m_pMixChunk != nullptr;
}

bool SoundEffect::Play( int loops )
{
	if (m_IsLooping)
		loops = -1;

	// Don't save the channel as a data member, 
	// because when it stops playing the channel becomes free
	// and available for usage by other effects
	if ( m_pMixChunk != nullptr )
	{
		m_Channel =  Mix_PlayChannel( -1, m_pMixChunk, loops ) ;
		return m_Channel == -1 ? false : true;
	}
	else
	{
		return false;
	}
}

void SoundEffect::Stop()
{
	Mix_HaltChannel(m_Channel);
}

void SoundEffect::SetVolume( const int value )
{
	if ( m_pMixChunk != nullptr )
	{
		Mix_VolumeChunk( m_pMixChunk, value );
	}
}

int SoundEffect::GetVolume( ) const
{
	if ( m_pMixChunk != nullptr )
	{
		return Mix_VolumeChunk( m_pMixChunk, -1 );
	}
	else
	{
		return -1;
	}
}

void SoundEffect::StopAll( )
{
	Mix_HaltChannel(-1 );
}

void SoundEffect::PauseAll( )
{
	Mix_Pause( -1 );
}
void SoundEffect::ResumeAll( )
{
	Mix_Resume( -1 );
}




