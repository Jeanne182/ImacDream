#include "../include/App.hpp"

void App::event(const SDL_Event &e) {
    if (_layout = LAYOUT_GAME){
        _game.event(e);
    }

}

void App::draw() {
    switch(_layout){
        case LAYOUT_GAME:
            drawGame();
            break;
    }
}

void App::drawGame() {
    try{
        _game.update();
        _game.display();
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
}
