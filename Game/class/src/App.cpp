#include "../include/App.hpp"

void App::event(const SDL_Event &e) {
    _game.event(e);
}

void App::update() {
    _game.update();
}

void App::display(glm::mat4 &projMatrix, Program &program, GLint &M_Location, GLint &MV_Location, GLint &MVP_Location,
                  GLint &N_Location) {
    _game.display(projMatrix, program, M_Location, MV_Location, MVP_Location, N_Location);
}
