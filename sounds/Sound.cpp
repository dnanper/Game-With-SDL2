#include "Sound.h"

Sound* Sound::s_Instance = nullptr;

Sound::Sound()
{
    if ( Mix_OpenAudio(FREQ, MIX_DEFAULT_FORMAT, 2, CHUNK_SIZE) < 0 )
    {
        std::cerr << Mix_GetError() << std::endl;
    }
}

// music

void Sound::PlayMusic(std::string id)
{
    if ( Mix_PlayMusic(m_MusicMap[id], -1) == -1 )
    {
        std::cerr << Mix_GetError() << ": " << id << std::endl;
    }
}

void Sound::LoadMusic(std::string id, std::string source)
{
    Mix_Music* music = Mix_LoadMUS(source.c_str());
    if ( music != nullptr)
    {
        m_MusicMap[id] = music;
    }
    else
        std::cerr << Mix_GetError() << ": " << source << std::endl;
}

//chunk

void Sound::PlayEffect(std::string id)
{
    if ( Mix_PlayChannel(-1, m_EffectMap[id], 0) == -1 )
    {
        std::cerr << Mix_GetError() << ": " << id << std::endl;
    }
}

void Sound::LoadEffect(std::string id, std::string source)
{
    Mix_Chunk* effect = Mix_LoadWAV(source.c_str());
    if ( effect != nullptr)
    {
        m_EffectMap[id] = effect;
    }
    else
        std::cerr << Mix_GetError() << ": " << source << std::endl;
}

void Sound::Clean()
{
    for ( MusicMap::iterator it = m_MusicMap.begin(); it != m_MusicMap.end(); it ++)
    {
        Mix_FreeMusic(it->second);
    }
    for ( EffectMap::iterator it = m_EffectMap.begin(); it != m_EffectMap.end(); it ++)
    {
        Mix_FreeChunk(it->second);
    }
    m_MusicMap.clear();
    m_EffectMap.clear();
    std::cout << "Sound system cleaned! \n";
}