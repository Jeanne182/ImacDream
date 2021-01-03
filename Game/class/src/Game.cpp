#include "../include/Game.hpp"
#include "../include/AssetsManager.hpp"


void Game::event(const SDL_Event &e) {
    collisionsManager(10.f);
    _camera.event(e, _move);
    ResetMove();
    _pointLight.event(e);
    _map->event(e,_camera.getViewMatrix());
}

void Game::update() {
    collisionsManager(3.f);
    _camera.update(_move);
    ResetMove();
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

void Game::ResetMove(){
    _move["UP"]=true;
    _move["DOWN"]=true;
    _move["LEFT"]=true;
    _move["RIGHT"]=true;
}

void Game::collisionsManager(const float t){
    _camera.setFuturesPositions(t);
    checkCollisions(getMap()->getTerrain()->getNbTree(), getMap()->getTerrain()->getTreesCenters());
    checkCollisions(getMap()->getTerrain()->getNbMenhirs(), getMap()->getTerrain()->getMenhirsCenters());

}


void Game::checkCollisions(const int nbObj, const std::vector<std::pair<glm::vec3, float>> CenterRadius){
    //With the edges of the map
    for(auto it : getCamera().getFuturesPositions()){
        if(it.second.x < -490  || it.second.x > 490
            || it.second.z < -490  || it.second.z > 490) _move[it.first]=false;
    }


    //With Trees and Menhirs
    for(int i=0; i<nbObj; i++){
        if(glm::distance(getCamera().getFuturesPositions()["UP"], CenterRadius[i].first) < CenterRadius[i].second){
            _move["UP"]=false;
        }
        if(glm::distance(getCamera().getFuturesPositions()["DOWN"], CenterRadius[i].first) < CenterRadius[i].second){
            _move["DOWN"]=false;
        }
        if(glm::distance(getCamera().getFuturesPositions()["LEFT"], CenterRadius[i].first) < CenterRadius[i].second){
            _move["LEFT"]=false;
        }
        if(glm::distance(getCamera().getFuturesPositions()["RIGHT"], CenterRadius[i].first) < CenterRadius[i].second){
            _move["RIGHT"]=false;
        }
    }
}

void Game::ResetGame(){
    setScore(0);
    std::cout <<_score<< std::endl;

    _pointLight.setLightOn(true);
    _pointLight.setShininess(10.f);
    _pointLight.setPosition(glm::vec4(0.f, 1.f, 0.f, 0.f));
    _pointLight.setIntensity();
    _camera.setPosition(glm::vec3(0., 4., 0.));
    std::cout << _camera.getPosition()<< std::endl;
    ResetMove();
    _map->getTerrain()->randomizeManager();

}