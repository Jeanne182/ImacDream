#include "../include/MapManager.hpp"
#include "../include/AssetsManager.hpp"
#include "../include/Utils.hpp"



void MapManager::display(const glm::mat4 &cameraView) {
    _terrain.displayManager(cameraView);

    glEnable (GL_BLEND);
    glBlendEquation(GL_ADD);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    AssetManager::Get()->_waterProgram._program.use();

    _water.computeMatrix(cameraView);
    _water.useMatrix();
    _water.displayWater();
    glDisable(GL_BLEND);

}

void MapManager::event(const SDL_Event &e, const glm::mat4 &cameraView) {
    switch(e.type){
        case SDL_KEYDOWN:
            if (e.key.keysym.sym==SDLK_e){


            }

            break;
    }
}




