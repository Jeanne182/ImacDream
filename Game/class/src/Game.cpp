#include "../include/Game.hpp"


void Game::event(const SDL_Event &e) {
    _camera.event(e);
    _pointLight.event(e);
    _map->event(e,_camera.getViewMatrix(), _camera.getPosition());
}

void Game::update() {
    //float newY = _map->getTerrainHeight(_camera.getPosition().x, _camera.getPosition().z);
    //_camera.setPositionY((newY+_camera.getPosition().y)/2.);
    _camera.setPositionY(-10);

    _camera.update();
    _pointLight.useMatrix(_camera.getViewMatrix());
}

void Game::display() {
    _map->display(_camera.getViewMatrix());
}
