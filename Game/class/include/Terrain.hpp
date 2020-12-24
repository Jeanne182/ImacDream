#ifndef IMACDREAM_TERRAIN_HPP
#define IMACDREAM_TERRAIN_HPP

#include "./GameObject.hpp"
#include <vector>


class Terrain {
private:
    std::vector<GameObject> _objects;

public:
    Terrain(std::vector<GameObject> &objects);
    void computeMatrix(const glm::mat4 &cameraView, glm::mat4 &projMatrix);
    void display(Program &program, GLint &M_Location, GLint &MV_Location, GLint &MVP_Location, GLint &N_Location);
    void deleteBuffers();
};

std::vector<GameObject>* ObjectsManager(const FilePath &applicationPath);

#endif //IMACDREAM_TERRAIN_HPP
