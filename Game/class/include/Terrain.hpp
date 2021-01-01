#ifndef IMACDREAM_TERRAIN_HPP
#define IMACDREAM_TERRAIN_HPP

#include "./GameObject.hpp"
#include <vector>
#include <map>

enum TerrainObjects{
    TREE,
    TERRAIN
};

class Terrain {
private:
//    std::vector<GameObject> _objects;
//    std::vector<GameObject> _objectsDisplayed;
    std::vector<GameObject> _objects;
    std::map<const std::string, GameObject*> _objectsDisplayed;

public:

    inline Terrain(){ ObjectsManager();};
    Terrain(std::vector<GameObject> &objects);
    void display(const glm::mat4 &cameraView);
    void deleteBuffers();
    void ObjectsManager();


    //GETTERS

};



#endif //IMACDREAM_TERRAIN_HPP
