#include "../include/Light.hpp"
#include "../include/AssetsManager.hpp"

void Light::event(const SDL_Event &e) {
//    switch(e.type) {
//        case SDL_KEYDOWN:
//            if (e.key.keysym.sym==SDLK_a)
//            {
//                if(!getLightOn()){
//                    setIntensity(10.f);
//                    setLightOn(true);
//                    glUniform3fv(AssetManager::Get()->_lightProgram.LightIntensity_Location(), 1, glm::value_ptr(getIntensity()));
//                    std::cout<<getIntensity()<<std::endl;
//                }
//                else{
//                    setIntensity(0.f);
//                    setLightOn(false);
//                    glUniform3fv(AssetManager::Get()->_lightProgram.LightIntensity_Location(), 1, glm::value_ptr(getIntensity()));
//                    std::cout<<getIntensity()<<std::endl;
//
//                }
//            };
//            break;
//        default:
//            break;
//    }
}

void Light::useMatrix(const glm::mat4 &cameraView) {
    glUniform3fv(AssetManager::Get()->_lightProgram.ViewPos_Location(), 1, glm::value_ptr(cameraView));
    glUniform3fv(AssetManager::Get()->_lightProgram.LightPos_Location(), 1, glm::value_ptr(getPosition()));
    glUniform1f(AssetManager::Get()->_lightProgram.Shininess_Location(), getShininess());

    glUniform3fv(AssetManager::Get()->_lightProgram.LightIntensity_Location(), 1, glm::value_ptr(getIntensity()));
}

