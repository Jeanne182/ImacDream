#include "../include/Light.hpp"
#include "../include/AssetsManager.hpp"

void Light::event(const SDL_Event &e) {
    switch(e.type) {
        case SDL_KEYDOWN:
            if (e.key.keysym.sym==SDLK_a)
            {
                if(!getLightOn()){
                    setIntensity(70.);
                    setLightOn(true);}
                else{
                    setIntensity(20.);
                    setLightOn(false);
                }
            };
            break;
        default:
            break;
    }
}

void Light::useMatrix(const glm::mat4 &cameraView) {
    glUniform3fv(AssetManager::Get()->_multiLightsProgram.ViewPos_Location(), 1, glm::value_ptr(cameraView));
    glUniform1f(AssetManager::Get()->_multiLightsProgram.Shininess_Location(), getShininess()); // taille de la tache glossy
    glUniform3fv(AssetManager::Get()->_multiLightsProgram.LightPos_Location(), 1, glm::value_ptr(getPosition()));
    glUniform3fv(AssetManager::Get()->_multiLightsProgram.LightIntensity_Location(), 1, glm::value_ptr(getIntensity()));
}

