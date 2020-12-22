#ifndef IMACDREAM_MAPMANAGER_HPP
#define IMACDREAM_MAPMANAGER_HPP

#include "./Terrain.hpp"
#include "./Camera.hpp"

class MapManager {
private:
    Terrain _terrain;
public:
    inline MapManager(const FilePath &applicationPath):_terrain(applicationPath){}
    void display(glm::mat4 &cameraView, glm::mat4 &projMatrix, Program &program, GLint &M_Location, GLint &MV_Location, GLint &MVP_Location, GLint &N_Location);
};


#endif //IMACDREAM_MAPMANAGER_HPP
