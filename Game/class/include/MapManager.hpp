#ifndef IMACDREAM_MAPMANAGER_HPP
#define IMACDREAM_MAPMANAGER_HPP

#include <glimac/SDLWindowManager.hpp>
#include "./Terrain.hpp"
#include "./Camera.hpp"
#include "./InteractiveObjectManager.hpp"
#include "./Water.hpp"



class MapManager {
private:
    Terrain _terrain;
    InteractiveObjectManager _interactiveObjectManager;
    Water _water;
public:

    inline MapManager():_terrain(), _interactiveObjectManager(), _water(){}
    void display(const glm::mat4 &cameraView);
    inline void Delete(){ _terrain.deleteBuffers(); _interactiveObjectManager.deleteBuffers();};
    void event(const SDL_Event &e, glm::vec3 cameraPosition);

};

#endif //IMACDREAM_MAPMANAGER_HPP
