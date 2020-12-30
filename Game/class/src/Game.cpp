#include "../include/Game.hpp"
#include "../include/AssetsManager.hpp"

void Game::event(const SDL_Event &e) {
//    switch(e.type){
//        case SDL_KEYDOWN:
//            _pointLight._lightOn = true;
//            std::cout<<_pointLight._lightOn<<std::endl;
//            break;
//        default:
//            //_pointLight.setIntensity(50.f);
//            break;
//    }
//    _pointLight.setIntensity();
//    _pointLight.useMatrix(_camera.getViewMatrix());
    _camera.event(e);
    _pointLight.event(e);


    //update();

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
        case SDL_KEYDOWN:
            if (e.key.keysym.sym==SDLK_a)
            {
                if(!_pointLight.getLightOn()){
                    std::cout<<_pointLight.getLightOn()<<std::endl;

                    _pointLight.setIntensity();
                    std::cout<<_pointLight.getIntensity()<<std::endl;
                    std::cout<<"a pressed true"<<std::endl;
                }
                else {
                    _pointLight.setIntensity();
                    std::cout<<_pointLight.getIntensity()<<std::endl;
                    std::cout<<"a pressed false"<<std::endl;
                }
            };
            break;
    }
}

void Game::update() {
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
