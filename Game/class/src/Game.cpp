#include "../include/Game.hpp"
#include "../include/AssetsManager.hpp"


void Game::event(const SDL_Event &e) {
    _camera.event(e);
    _pointLight.event(e);
    _map->event(e,_camera.getViewMatrix());
}

void Game::update() {
    _camera.setPositionY(8.f);
    //if(collisions(_))
    //if collisions de cam.futurepos ==true
    _camera.update();
    _pointLight.useMatrix(_camera.getViewMatrix());
    _pointLight.updateTime();
}

void Game::display() {
    AssetManager::Get()->_lightProgram._program.use();
    _map->display(_camera.getViewMatrix());

    AssetManager::Get()->_skyboxProgram._program.use();
    _sky.computeMatrix(_camera.getViewMatrix());
    _sky.useMatrix();
    _sky.DrawSky();
}

