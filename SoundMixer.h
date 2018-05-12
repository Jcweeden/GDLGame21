#ifndef _SOUNDMIXER_
#define _SOUNDMIXER_

#include "SDL2/SDL_mixer.h"

#include <map>
#include <string>
#include <iostream>

enum soundType
{
SOUND_MUSIC = 0,
  SOUND_SFX = 1
    };

class SoundMixer {

public:
static SoundMixer* Instance();

bool load(std::string fileName, std::string id, soundType type);

void playSound (std::string id, int loop);
void playMusic (std::string id, int loop);


private:
SoundMixer();
~SoundMixer();

static SoundMixer* s_pInstance;


std::map<std::string, Mix_Chunk*> m_sfxs;
std::map<std::string, Mix_Music*> m_music;

};

typedef SoundMixer TheSoundMixer;

#endif
