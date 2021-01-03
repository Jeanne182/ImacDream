#ifndef IMACDREAM_APP_HPP
#define IMACDREAM_APP_HPP

#include <glimac/SDLWindowManager.hpp>
#include "../include/Game.hpp"
#include "../include/Music.hpp"
#include "../include/StaticImage.hpp"
#include "../include/Text.hpp"
#include <time.h>

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
    Music _music;
    StaticImageManager _staticImages;
    TextsManager _texts;
    CharactersManager _characters;
    int _layout;
    clock_t _time = clock();

public:
    //CONSTRUCTOR
    inline App():_game(), _music("musique"), _texts(), _characters(), _layout(LAYOUT_MENU){_music.play(-1);};
    ~App()=default;

    //DRAW FUNCTIONS
    void draw();
    void drawMenu();
    void drawGame();
    void drawGameOver();
    void event(const SDL_Event &e);
    inline void Delete(){ _game.Delete(); _texts.Delete(); _characters.Delete(); _music.Delete(); };

    //LAYOUTS
    static void layout2D();
    static void layout3D();
    void layoutGame();
};


#endif //IMACDREAM_APP_HPP
