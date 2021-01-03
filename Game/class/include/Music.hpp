#ifndef IMACDREAM_MUSIC_H
#define IMACDREAM_MUSIC_H
#include <SDL2/SDL_mixer.h>
#include <map>

class Music {
    public:
        Music(const std::string &musicName);

        void Delete();
        void play(const int loop);

private:
        Mix_Chunk*_music = NULL;
};

#endif //IMACDREAM_MUSIC_H
