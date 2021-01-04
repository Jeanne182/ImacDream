#include "../include/Music.hpp"
#include "../include/AssetsManager.hpp"
#include <SDL2/SDL_mixer.h>

Music::Music(const std::string &musicName) {
    Mix_AllocateChannels(5);
    //Init music
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) ==-1) //Initialisation de l'API Mixer
    {
        printf("Opening MIX_AUDIO: %s\n", Mix_GetError());
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME); //Mettre le volume à la moitié

    const char* musicpath = (musicName + ".wav").c_str();
    _music = Mix_LoadWAV((AssetManager::Get()->appPath().dirPath() + "/Assets/music/" + musicpath).c_str()); //Chargement de la musique

    if (_music == nullptr) printf("Mix_LoadMUS: %s\n", Mix_GetError());
}

void Music::Delete() {
    Mix_FreeChunk(_music);
    Mix_CloseAudio();
}

void Music::play(const int loop)
{
    if(Mix_PlayChannel(-1, _music, loop)==-1)
        printf("Play Channel: %s\n", Mix_GetError());
}