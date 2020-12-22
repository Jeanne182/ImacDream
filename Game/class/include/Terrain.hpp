#ifndef IMACDREAM_TERRAIN_HPP
#define IMACDREAM_TERRAIN_HPP

#include "./GameObject.hpp"
#include <vector>

enum class TerrainObjects{
    SPHERE,
    TREE,
    TRUNK
};

class Terrain {
private:
    std::vector<GameObject> _objects;
    std::vector<GameObject> _objectsDisplayed;

public:
    inline Terrain(const FilePath &applicationPath){ ObjectsManager(applicationPath); };
    inline Terrain(std::vector<GameObject> &objects):_objects(objects){};
    void display(const glm::mat4 &cameraView, glm::mat4 &projMatrix, Program &program, GLint &M_Location, GLint &MV_Location, GLint &MVP_Location, GLint &N_Location);
    void deleteBuffers();
    void ObjectsManager(const FilePath &applicationPath);
};



#endif //IMACDREAM_TERRAIN_HPP
