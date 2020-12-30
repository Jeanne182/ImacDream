#include "../include/MapManager.hpp"
#include "../include/Utils.hpp"

void MapManager::display(const glm::mat4 &cameraView) {
    _terrain.display(cameraView);
    _interactiveObjectManager.display(cameraView);
//    _water._model->_meshes[0].deleteBuffers();
//    _water.move();
//    _water._model->_meshes[0].setupMesh();
//    std::cout<<"Number of vertices : "<< _water._model->_meshes[0]._vertices.size()<<" & number of indexes  : "<<_water._model->_meshes[0]._indices.size()<<std::endl;
    _water.update(cameraView);
}

void MapManager::event(const SDL_Event &e, glm::vec3 cameraPosition) {
    switch(e.type){
        case SDL_KEYDOWN:
            if (e.key.keysym.sym==SDLK_n){
                //std::cout << "terrain position : " << getTerrainheight(cameraPosition.x, cameraPosition.z) << std::endl;;

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



