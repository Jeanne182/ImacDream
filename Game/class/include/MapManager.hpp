#ifndef IMACDREAM_MAPMANAGER_HPP
#define IMACDREAM_MAPMANAGER_HPP

#include "./Terrain.hpp"
#include "./Camera.hpp"
#include "./InteractiveObject.hpp"

class MapManager {
private:
    Terrain _terrain;
    std::vector<InteractiveObject> _interactiveObjects;

public:
    inline MapManager():_terrain(), _interactiveObjects() {}
    void display(const glm::mat4 &cameraView);
    inline void Delete(){ _terrain.deleteBuffers(); };

    //GETTERS
    inline std::vector<InteractiveObject> interactiveObjects(){ return _interactiveObjects; };
};

#endif //IMACDREAM_MAPMANAGER_HPP
