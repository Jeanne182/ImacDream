//#include "../include/Music.hpp"
//#include "../include/AssetsManager.hpp"
//#include <SDL2/SDL_mixer.h>
//
//Music::Music() {
//    //Init music
//    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) //Initialisation de l'API Mixer
//    {
//        printf("Opening MIX_AUDIO: %s\n", Mix_GetError());
//    }
//
//    Mix_VolumeMusic(MIX_MAX_VOLUME); //Mettre le volume à la moitié
//    _game = Mix_LoadMUS((AssetManager::Get()->appPath().dirPath() + "Assets/music/musique.mp3").c_str()); //Chargement de la musique
//    if (_game != nullptr)
//        printf("Loaded the file\n");
//    else
//        printf("Mix_LoadMUS: %s\n", Mix_GetError());
//
//}
//
//void Music::Delete() {
//    Mix_FreeMusic(_game);
//    Mix_CloseAudio();
//}
//
//void Music::playGame()
//{
//    Mix_PlayMusic(_game, -1);
//}