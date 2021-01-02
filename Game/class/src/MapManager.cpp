#include "../include/MapManager.hpp"
#include "../include/AssetsManager.hpp"
#include "../include/Utils.hpp"



void MapManager::display(const glm::mat4 &cameraView) {
    _terrain.displayManager(cameraView);
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
                /*std::cout << "elements in mymap:" << '\n';
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



