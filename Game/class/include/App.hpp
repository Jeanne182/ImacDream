#ifndef IMACDREAM_APP_HPP
#define IMACDREAM_APP_HPP

#include <glimac/SDLWindowManager.hpp>
#include "../include/Game.hpp"
#include "../include/StaticImage.hpp"
#include "../include/Text.hpp"



using namespace glimac;

enum LAYOUT
{
    LAYOUT_DEFAULT,
    LAYOUT_MENU,
    LAYOUT_SCORES,
    LAYOUT_PAUSE,
    LAYOUT_GAME,
    LAYOUT_GAME_OVER
};

class App {
private:

    int _layout = LAYOUT_GAME;
    Game _game;
    StaticImageManager _staticImages;
    TextManager _texts;

public:
    //CONSTRUCTOR
    inline App():_game(){};



    void draw();
    void event(const SDL_Event &e);
    inline void Delete(){ _game.Delete(); };

    //LAYOUTS
    void drawGame();
    void layout2D();
    void layout3D();
    void layoutGame();

};


#endif //IMACDREAM_APP_HPP
