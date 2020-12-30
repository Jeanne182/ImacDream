#ifndef IMACDREAM_MAPMANAGER_HPP
#define IMACDREAM_MAPMANAGER_HPP

#include <glimac/SDLWindowManager.hpp>
#include "./Terrain.hpp"
#include "./Camera.hpp"
#include "./InteractiveObjectManager.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <map>
#include<tuple>
#include "./Water.hpp"



class MapManager {
private:
    Terrain _terrain;
    InteractiveObjectManager _interactiveObjectManager;
    std::map<std::tuple<int, int>, float> _mapTerrain;

    Water _water;
public:

    inline MapManager():_terrain(), _interactiveObjectManager(), _water(){}
    void display(const glm::mat4 &cameraView);
    inline void Delete(){ _terrain.deleteBuffers(); _interactiveObjectManager.deleteBuffers();};
    float getTerrainHeight(const float x, const float z);

    void event(const SDL_Event &e, glm::vec3 cameraPosition);

    //SETTERS
    void setMapTerrain();

};

#endif //IMACDREAM_MAPMANAGER_HPP
