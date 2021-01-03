#ifndef IMACDREAM_LIGHT_HPP
#define IMACDREAM_LIGHT_HPP

#include <glimac/glm.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <iostream>
#include <time.h>

class Light
{

private:
    float _LIGHT_ON_INTENSITY = 5.f;
    float _LIGHT_OFF_INTENSITY = 2.f;
    bool _lightOn;
    float _shininess;
    glm::vec4 _position;
    glm::vec3 _intensity;
    clock_t _time = clock();
    clock_t _elapsed = clock();

public:
    int _LIGHT_ON_TIMING = 10;
    int _LIGHT_OFF_TIMING = 20;
    inline Light():
            _lightOn(true), _shininess(10.f), _position(glm::vec4(0.f, 1.f, 0.f, 0.f)), _intensity(glm::vec3(_LIGHT_OFF_INTENSITY)) {
        setIntensity();
    };

    void setIntensity();
//    inline bool setLightOn(const bool state){ _lightOn = state;};

    inline glm::vec4 getPosition(){ return _position; };
    inline glm::vec3 getIntensity(){return _intensity; };
    inline float getShininess(){ return _shininess; };
    inline bool getLightOn(){return _lightOn;};
    void event(const SDL_Event &e);
    void useMatrix(const glm::mat4 &cameraView);
    void updateTime();

    inline int elapsedTime(){ return ((int)clock() - _time) / CLOCKS_PER_SEC; }
};

#endif //IMACDREAM_LIGHT_HPP
