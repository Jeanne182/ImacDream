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
    Game _game;
    int _layout = LAYOUT_GAME;

public:
    //Constructor
    inline App():_game(){};

    //Facades Functions
    void drawGame();

    void draw();
    void event(const SDL_Event &e);

};


#endif //IMACDREAM_APP_HPP
