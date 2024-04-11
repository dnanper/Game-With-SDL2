#ifndef SOUND_H
#define SOUND_H

#include <map>
#include <string>
#include <iostream>
#include "../inc/SDL_mixer.h"

#define FREQ 44100
#define CHUNK_SIZE 2048

using EffectMap = std::map<std::string, Mix_Chunk*>;
using MusicMap = std::map<std::string, Mix_Music*>;

class Sound
{
    public:
        void Clean();

        void PlayMusic(std::string id);
        void LoadMusic(std::string id, std::string source);

        void PlayEffect(std::string id);
        void LoadEffect(std::string id, std::string source);

        inline static Sound* GetInstance() { return s_Instance = (s_Instance != nullptr)? s_Instance : new Sound(); }

    private:
        Sound();
        MusicMap m_MusicMap;
        EffectMap m_EffectMap;
        static Sound *s_Instance;
};

#endif  // SOUND_H