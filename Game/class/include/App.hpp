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
    int _width, _height, _ratio;
    SDLWindowManager windowManager;
    Game _game;
    int _layout = LAYOUT_GAME;

public:
    //Constructor
    App(const int &width, const int &height, const FilePath &applicationPath):
        _width(width),
        _height(height),
        _ratio((float)width/height),
        _game(0),
        windowManager(width, height, "GLImac")
        {};

    //Layouts
    void layout2D();
    void layoutMenu();
    void layoutGame();

    //Facades Functions
    void display(glm::mat4 &projMatrix, Program &program, GLint &M_Location, GLint &MV_Location, GLint &MVP_Location, GLint &N_Location);
    void event(const SDL_Event &e);
    void update();

};


#endif //IMACDREAM_APP_HPP
