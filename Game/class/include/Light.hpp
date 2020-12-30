#ifndef IMACDREAM_LIGHT_HPP
#define IMACDREAM_LIGHT_HPP

#include <glimac/glm.hpp>
#include <glimac/SDLWindowManager.hpp>

class Light
{
public:
    inline Light()
        :_position(glm::vec4(0.f, 0.f, 0.f, 0.f)), _intensity(glm::vec3(0.f)), _lightOn(false){};
    inline Light(const glm::mat4 &cameraView):
        _position(glm::vec4(0.f, 1.f, 0.f, 0.f)),_intensity(glm::vec3(0.f)), _lightOn(false){};

    inline void setIntensity(const float intensity){ _intensity = glm::vec3(intensity); };
    inline bool setLightOn(const bool state){ _lightOn = state;};

    inline glm::vec4 getPosition(){ return _position; };
    inline glm::vec3 getIntensity(){ return _intensity; };
    inline bool getLightOn(){return _lightOn;};

    void event(const SDL_Event &e);
    void useMatrix(const glm::mat4 &cameraView);

private:
    glm::vec4 _position;
    glm::vec3 _intensity;
    bool _lightOn;
};
#endif //IMACDREAM_LIGHT_HPP
