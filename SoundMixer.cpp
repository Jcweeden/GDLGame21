#include "SoundMixer.h"
//#include "SDL/SDL_mixer.h"
#include <unistd.h>


SoundMixer* SoundMixer::s_pInstance = 0;


SoundMixer* SoundMixer::Instance()
{
  if(s_pInstance == 0)
  {
    s_pInstance = new SoundMixer();
    return s_pInstance;
  }
  return s_pInstance;
}


SoundMixer::SoundMixer()
{
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, (4096));
}

SoundMixer::~SoundMixer()
{
  Mix_CloseAudio();
}

bool SoundMixer::load(std::string fileName, std::string id, soundType type)
{
   if(type == SOUND_MUSIC)
    {
        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
        if(pMusic == 0)
        {
            std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        
        m_music[id] = pMusic;
        return true;
    }
    else if(type == SOUND_SFX)
    {
        Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
        if(pChunk == 0)
        {
            std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        
        m_sfxs[id] = pChunk;
        return true;
    }
    return false;
}

void SoundMixer::playMusic(std::string id, int loop)
{
  Mix_PlayMusic(m_music[id], loop);
}

void SoundMixer::playSound(std::string id, int loop)
{
  Mix_PlayChannel(2, m_sfxs[id], loop);
}

void SoundMixer::playSpawned(std::string id, int loop)
{
  Mix_PlayChannel(3, m_sfxs[id], loop);
}
