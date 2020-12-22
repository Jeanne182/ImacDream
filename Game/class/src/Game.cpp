#include "../include/Game.hpp"

void Game::event(const SDL_Event &e) {
    _camera.event(e);
}

void Game::update() {
    _camera.update();
}

void Game::display(glm::mat4 &projMatrix, Program &program, GLint &M_Location, GLint &MV_Location, GLint &MVP_Location,
                   GLint &N_Location) {
    auto* viewMatrix = new glm::mat4(_camera.getViewMatrix()) ;
    _mapManager.display(*viewMatrix, projMatrix, program, M_Location, MV_Location, MVP_Location, N_Location);
}
