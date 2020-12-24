#include "../include/Game.hpp"

void Game::event(const SDL_Event &e) {
    _camera.event(e);
}

void Game::update() {
    _camera.update();
}

void Game::display() {
    _map->display(_camera.getViewMatrix());
}
