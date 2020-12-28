#ifndef IMACDREAM_MAPMANAGER_HPP
#define IMACDREAM_MAPMANAGER_HPP

#include "./Terrain.hpp"
#include "./Camera.hpp"
#include "./InteractiveObjectManager.hpp"
#include <glimac/SDLWindowManager.hpp>


class MapManager {
private:
    Terrain _terrain;
    InteractiveObjectManager _interactiveObjectManager;
public:

    inline MapManager():_terrain(), _interactiveObjectManager(){}
    void display(const glm::mat4 &cameraView);
    inline void Delete(){ _terrain.deleteBuffers(); _interactiveObjectManager.deleteBuffers();};

    void event(const SDL_Event &e, glm::vec3 cameraPosition);

};

#endif //IMACDREAM_MAPMANAGER_HPP
