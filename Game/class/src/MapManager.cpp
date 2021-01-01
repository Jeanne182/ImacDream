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
    corners.push_back(glm::vec3(std::get<0>(low->first)/100., std::get<1>(low->first)/100., low->second));
    prev = std::prev(low);
    corners.push_back(glm::vec3(std::get<0>(prev->first)/100., std::get<1>(prev->first)/100., prev->second));
    return corners;

}
/*
glm::vec3 MapManager::getUpperBound(const float x, const float z){
    std::map<std::tuple<int, int>, float>::iterator up;
    std::tuple<int, int> pos = std::tuple<int, int>(x*100, z*100);
    up = _mapTerrain.lower_bound(pos);
    return glm::vec3(std::get<0>(up->first)/100., std::get<1>(up->first)/100., up->second);
}

*/
/*
void MapManager::getY(const float x, const float z){
    float TerrainX = x - _terrain._objects[TERRAIN].getPosition().x;
    float TerrainZ = z - _terrain._objects[TERRAIN].getPosition().z;
    float gridSquareSize = _terrain._objects[TERRAIN].getHitboxRadius()*2/_terrain._objects[TERRAIN]._model->_meshes->mNumFaces(_terrain._objects[TERRAIN]);

}*/

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

void MapManager::event(const SDL_Event &e, const glm::mat4 &cameraView, const glm::vec3 &cameraPosition) {
    switch(e.type){
        case SDL_KEYDOWN:
            if (e.key.keysym.sym==SDLK_n){


                //std::cout <<"Y =  : " <<getTerrainHeight(cameraPosition.x, cameraPosition.z)<< std::endl;
                //std::cout <<"cam : " << cameraPosition.x << " "<< cameraPosition.z << std::endl;
/*                //std::cout <<"lower : " << getLowerBound(cameraPosition.x, cameraPosition.z)[0] << std::endl;
                //std::cout <<"prev : " << getLowerBound(cameraPosition.x, cameraPosition.z)[1] << std::endl;

                //std::cout <<"upper : " << getUpperBound(cameraPosition.x, cameraPosition.z) << std::endl;

                std::cout << "elements in mymap:" << '\n';
                std::map<std::tuple<int, int>, float>::iterator p; //Création d'un itérator sur le 'map'
                for(p = _mapTerrain.begin(); p != _mapTerrain.end(); p++){
                    std::cout <<"X value : " << std::get<0>(p->first)/100 << std::endl;
                    std::cout <<"Z value : " << std::get<1>(p->first)/100 << std::endl;
                    std::cout << "Height value : "<< p->second << std::endl;
                }
                //std::cout << "terrain position : " << getTerrainheight(cameraPosition.x, cameraPosition.z) << std::endl;
*/

                int egg_id = _interactiveObjectManager.selectedEgg(cameraView, cameraPosition);
                //std::cout << "id : " << egg_id << std::endl;
                if(egg_id != -1){
                    std::cout << "Object selected" << std::endl;
                    _interactiveObjectManager.setBoolValue(egg_id);
                    //score a augmenter

                }

            }

            break;
    }
}



