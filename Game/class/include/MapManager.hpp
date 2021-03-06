#ifndef IMACDREAM_MAPMANAGER_HPP
#define IMACDREAM_MAPMANAGER_HPP

#include <glimac/SDLWindowManager.hpp>
#include "./Terrain.hpp"
#include "./Camera.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <map>
#include<tuple>
#include "./Water.hpp"



class MapManager {
private:
    Terrain _terrain;
    Water _water;
public:

    inline MapManager():_terrain(), _water(){}
    ~MapManager()=default;
    void display(const glm::mat4 &cameraView);
    inline void Delete(){ _terrain.deleteBuffers(); _water.deleteBuffers();};


    //SETTERS

    //GETTERS
    inline Terrain* getTerrain(){ return &_terrain;};

};

#endif //IMACDREAM_MAPMANAGER_HPP
