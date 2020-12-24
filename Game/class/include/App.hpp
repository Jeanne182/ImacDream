#ifndef IMACDREAM_APP_HPP
#define IMACDREAM_APP_HPP

#include <glimac/SDLWindowManager.hpp>
#include "../include/Game.hpp"

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

public:
    //Constructor
    inline App():_game(){};

    //Facades Functions
    void drawGame();

    void draw();
    void event(const SDL_Event &e);
    inline void Delete(){ _game.Delete(); };

};


#endif //IMACDREAM_APP_HPP
