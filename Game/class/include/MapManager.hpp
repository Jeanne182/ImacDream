#ifndef IMACDREAM_MAPMANAGER_HPP
#define IMACDREAM_MAPMANAGER_HPP

#include "./Terrain.hpp"
#include "./Camera.hpp"
#include "./InteractiveObjectManager.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <map>
#include<tuple>


class MapManager {
private:
    Terrain _terrain;
    InteractiveObjectManager _interactiveObjectManager;

public:
    inline MapManager():_terrain(), _interactiveObjectManager(){}
    void display(const glm::mat4 &cameraView);
    inline void Delete(){ _terrain.deleteBuffers(); _interactiveObjectManager.deleteBuffers();};

    //std::vector<glm::vec3> getLowerBound(const float x, const float z);
    //glm::vec3 getUpperBound(const float x, const float z);


        void event(const SDL_Event &e,const glm::mat4 &cameraView, const glm::vec3 &cameraPosition);

    //SETTERS

};

#endif //IMACDREAM_MAPMANAGER_HPP
