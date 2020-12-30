//#include "../include/Music.hpp"
//#include "../include/AssetsManager.hpp"
//
//Music::Music() {
//    //Init music
//    Mix_Init(0);
//    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
//    {
//        printf("Opening MIX_AUDIO: %s\n", Mix_GetError());
//    }
//
//    Mix_VolumeMusic(MIX_MAX_VOLUME / 2); //Mettre le volume à la moitié
//    _game = Mix_LoadMUS((AssetManager::Get()->appPath().dirPath() + "Assets/music/musique.mp3").c_str()); //Chargement de la musique
//    if (_game != nullptr)
//        printf("Loaded the file\n");
//    else
//        printf("Mix_LoadMUS: %s\n", Mix_GetError());
//    if(Mix_PlayMusic(_game, -1)==-1) {
//        printf("Mix_PlayMusic: %s\n", Mix_GetError());
//    }
//}
//
//void Music::Delete() {
//    Mix_FreeMusic(_game);
//    delete _game;
//    Mix_CloseAudio();
//}
//
//void Music::playGame()
//{
//    Mix_PlayMusic(_game, -1);
//}