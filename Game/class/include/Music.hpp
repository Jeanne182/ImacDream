//#ifndef IMACDREAM_MUSIC_H
//#define IMACDREAM_MUSIC_H
//#include <SDL2/SDL_mixer.h>
//
//
//class Music {
//    public:
//        Music();
//
//        void Delete();
//        void playGame();
//
//    private:
//        Mix_Music *_game=NULL;
//};
//
//#endif //IMACDREAM_MUSIC_H


class Music {
    public:
        Music();

        void Delete();
        void playGame();

    private:
        Mix_Music *_game = NULL;
};

#endif //IMACDREAM_MUSIC_H
