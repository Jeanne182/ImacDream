#include "../include/MapManager.hpp"
#include "../include/AssetsManager.hpp"
#include "../include/Utils.hpp"


void MapManager::setMapTerrain() {
//    for(auto meshes : _terrain._objects[TERRAIN]._model->_meshes){
//        for(auto vertices : meshes._vertices){
//           _mapTerrain[std::make_tuple(vertices.position.x*100, vertices.position.z*100)] = vertices.position.y;
//
//        }
//    }
}

float MapManager::getTerrainHeight(const float x, const float z){
    std::map<std::tuple<int, int>, float>::iterator low, prev;
    std::tuple<int, int> pos = std::tuple<int, int>(x*100, z*100);
    low = _mapTerrain.lower_bound(pos);
    if (low == _mapTerrain.end()) {
        std::cout << "Position not find" << std::endl;
        // nothing found, maybe use rbegin()
    }
    else if (low == _mapTerrain.begin()) {
        std::cout << "low= " << std::get<0>(low->first) << " & " << std::get<1>(low->first) << std::endl;
    }
    else {
        prev = std::prev(low);
        if ((std::get<0>(pos) - std::get<0>(prev->first) && std::get<1>(pos) - std::get<1>(prev->first)) < (std::get<0>(low->first) - std::get<0>(pos) && std::get<1>(low->first) - std::get<1>(pos))){
            std::cout << "prev= " << std::get<0>(prev->first)/100 << " & " << std::get<1>(prev->first)/100 << std::endl;
            std::cout << "y= " << prev->second << std::endl;
        }

        else{
            std::cout << "low= " << std::get<0>(low->first)/100 << " & " << std::get<1>(low->first)/100 << std::endl;
            std::cout << "y= " << low->second << std::endl;

        }
    }
    return 0.f;
}

void MapManager::display(const glm::mat4 &cameraView) {
    _terrain.display(cameraView);
    setMapTerrain();
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
                getTerrainHeight(cameraPosition.x, cameraPosition.z);
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



