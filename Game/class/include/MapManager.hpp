#ifndef IMACDREAM_MAPMANAGER_HPP
#define IMACDREAM_MAPMANAGER_HPP

#include "./Terrain.hpp"
#include "./Camera.hpp"

class MapManager {
private:
    Terrain _terrain;
public:
    inline MapManager():_terrain(){}
    void display(const glm::mat4 &cameraView);
};


#endif //IMACDREAM_MAPMANAGER_HPP
