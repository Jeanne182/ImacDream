#include <SDL/SDL_mixer.h>

#ifndef IMACDREAM_MUSIC_H
#define IMACDREAM_MUSIC_H


class Music {
    public:
        Music();
        ~Music();
        void playGame();

    private:
        Mix_Music *_game;
};


#endif //IMACDREAM_MUSIC_H
