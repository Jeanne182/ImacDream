#include "../include/Light.hpp"
#include "../include/AssetsManager.hpp"
#include <stdio.h>


void Light::event(const SDL_Event &e) {

    switch(e.type) {
        case SDL_KEYDOWN:
            if (e.key.keysym.sym==SDLK_a)
            {
                if(!getLightOn() && _elapsed > _LIGHT_OFF_TIMING){
                    _lightOn = true;
                    _time = clock();
                }
                setIntensity();
            }
            break;
        default:
            break;
    }
}
void Light::setIntensity(){
    if(_lightOn) {
        _intensity = glm::vec3(_LIGHT_ON_INTENSITY);
    }
    else {
        _intensity = glm::vec3(_LIGHT_OFF_INTENSITY);
    }
}

void Light::updateTime() {
    double elapsed = ((int)clock() - _time) / CLOCKS_PER_SEC;
    if (elapsed != _elapsed ){
        _elapsed = elapsed;
    }
    if(_elapsed >= _LIGHT_ON_TIMING && _lightOn){
        _lightOn = false;
        _time = clock();
        setIntensity();
    }
}

void Light::useMatrix(const glm::mat4 &cameraView) {
    AssetManager::Get()->_lightProgram._program.use();
    glUniform3fv(AssetManager::Get()->_lightProgram.ViewPos_Location(), 1, glm::value_ptr(cameraView));
    glUniform3fv(AssetManager::Get()->_lightProgram.LightPos_Location(), 1, glm::value_ptr(getPosition()));
    glUniform1f(AssetManager::Get()->_lightProgram.Shininess_Location(), getShininess());
    glUniform3fv(AssetManager::Get()->_lightProgram.LightIntensity_Location(), 1, glm::value_ptr(getIntensity()));

    AssetManager::Get()->_waterProgram._program.use();
    glUniform3fv(AssetManager::Get()->_waterProgram.ViewPos_Location(), 1, glm::value_ptr(cameraView));
    glUniform3fv(AssetManager::Get()->_waterProgram.LightPos_Location(), 1, glm::value_ptr(getPosition()));
    glUniform1f(AssetManager::Get()->_waterProgram.Shininess_Location(), getShininess());
    glUniform3fv(AssetManager::Get()->_waterProgram.LightIntensity_Location(), 1, glm::value_ptr(getIntensity()));
}

