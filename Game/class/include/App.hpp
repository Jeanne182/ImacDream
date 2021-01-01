#ifndef IMACDREAM_APP_HPP
#define IMACDREAM_APP_HPP

#include <glimac/SDLWindowManager.hpp>
#include "../include/Game.hpp"
#include "../include/Music.hpp"
#include "../include/StaticImage.hpp"



using namespace glimac;

enum LAYOUT
{
    LAYOUT_MENU,
    LAYOUT_GAME,
    LAYOUT_GAME_OVER
};

class App {
private:

    Game _game;
//    Music _music;
    StaticImageManager _staticImages;
    int _layout;

public:


    //CONSTRUCTOR
//    inline App():_game(){_music.playGame(); };
    inline App():_game(), _layout(LAYOUT_GAME){};


    void draw();
    void event(const SDL_Event &e);
//    inline void Delete(){ _game.Delete(); _music.Delete(); };
    inline void Delete(){ _game.Delete();};


    //LAYOUTS
    void drawMenu();
    void drawGame();
    void drawGameOver();
    void layout2D();
    void layout3D();
    void layoutGame();

};


#endif //IMACDREAM_APP_HPP
