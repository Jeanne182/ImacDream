#include "../include/Light.hpp"

void Light::event(SDL_Event &e) {
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
