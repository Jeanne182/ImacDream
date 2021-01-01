#include "../include/MapManager.hpp"
#include "../include/AssetsManager.hpp"
#include "../include/Utils.hpp"



void MapManager::display(const glm::mat4 &cameraView) {
    _terrain.display(cameraView);
    _interactiveObjectManager.display(cameraView);

    glEnable (GL_BLEND);
    glBlendEquation(GL_ADD);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    AssetManager::Get()->_waterProgram._program.use();

    _water.computeMatrix(cameraView);
    _water.useMatrix();
    _water.displayWater();
    glDisable(GL_BLEND);

}

void MapManager::event(const SDL_Event &e, glm::vec3 cameraPosition) {
    switch(e.type){
        case SDL_KEYDOWN:
            if (e.key.keysym.sym==SDLK_n){
                /*std::cout << "elements in mymap:" << '\n';
                std::map<std::tuple<int, int>, float>::iterator p; //Création d'un itérator sur le 'map'
                for(p = _mapTerrain.begin(); p != _mapTerrain.end(); p++){
                    std::cout <<"X xalue : " << std::get<0>(p->first) << std::endl;
                    std::cout <<"Z value :  "<< std::get<1>(p->first) << std::endl;

                    std::cout << "Height value : "<< p->second << std::endl;
                }*/
                //std::cout << "terrain position : " << getTerrainheight(cameraPosition.x, cameraPosition.z) << std::endl;

/*
                for(auto objectToFind : _interactiveObjectManager._objectsToFind){

                    glm::vec3 P1 = glm::vec3(0., 0., 0.);
                    glm::vec3 P2 = glm::vec3(0., 0., 0.);
                    std::cout << "center : " <<objectToFind.getCenter()<<std::endl;

                    if(objectToFind.isSelected(cameraPosition, &P1, &P2)){
                        std::cout << "Object selected" << std::endl;
                        //Il faut enlever le objectToFind du vecteur mais comment ?
                        objectToFind.deleteBuffers();
                    }
                    else{
                        std::cout << "Object not selected" << std::endl;
                    }

                }*/
            }

            break;
    }
}



