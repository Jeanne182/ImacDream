#include "../include/Game.hpp"


void Game::event(const SDL_Event &e) {
    _camera.event(e);
    _pointLight.event(e);
    _map->event(e, _camera.getPosition());
}

void Game::update() {
    _camera.setPositionY(5.f);
    _camera.update();
    _pointLight.useMatrix(_camera.getViewMatrix());
}

void Game::display() {
    _map->display(_camera.getViewMatrix());
}
