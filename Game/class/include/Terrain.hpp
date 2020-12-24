#ifndef IMACDREAM_TERRAIN_HPP
#define IMACDREAM_TERRAIN_HPP

#include "./GameObject.hpp"
#include <vector>

enum TerrainObjects{
    SPHERE,
    TREE,
    TRUNK
};

class Terrain {
private:
    std::vector<GameObject> _objects;
    std::vector<GameObject> _objectsDisplayed;

public:
    inline Terrain(){ ObjectsManager(); };
    inline Terrain(std::vector<GameObject> &objects):_objects(objects){};
    void display(const glm::mat4 &cameraView);
    void deleteBuffers();
    void ObjectsManager();
};



#endif //IMACDREAM_TERRAIN_HPP
