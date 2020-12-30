#include "../include/Game.hpp"
#include "../include/AssetsManager.hpp"


void Game::event(const SDL_Event &e) {

    _camera.event(e);
    _pointLight.event(e);
    _map->event(e, _camera.getPosition());


    update();

    switch(e.type){
        case SDL_MOUSEBUTTONDOWN:
            for(auto objectToFind : _map->interactiveObjects()){
                glm::vec3 P1 = glm::vec3(0., 0., 0.);
                glm::vec3 P2 = glm::vec3(0., 0., 0.);

                if(objectToFind.isSelected(_camera.getPosition(), &P1, &P2)){
                    std::cout << "Object selected" << std::endl;
                }
                else{
                    std::cout << "Object not selected" << std::endl;
                }

            }
            break;
    }
}

void Game::update() {
    _camera.setPositionY(5.f);
    _camera.update();
    _pointLight.useMatrix(_camera.getViewMatrix());
}

void Game::display() {
    AssetManager::Get()->_lightProgram._program.use();
    _map->display(_camera.getViewMatrix());

    AssetManager::Get()->_skyboxProgram._program.use();
    _sky.computeMatrix(_camera.getViewMatrix());
    _sky.useMatrix();
    _sky.DrawSky();
}
