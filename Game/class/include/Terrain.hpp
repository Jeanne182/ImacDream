#ifndef IMACDREAM_TERRAIN_HPP
#define IMACDREAM_TERRAIN_HPP

#include "./GameObject.hpp"
#include <vector>

enum TerrainObjects{
    SPHERE,
    TREE,
    RUNE,
    TERRAIN,
};

class Terrain {
private:
//    std::vector<GameObject> _objects;
    std::vector<GameObject> _objectsDisplayed;

public:
    std::vector<GameObject> _objects;//PRIVATE

    inline Terrain(){ ObjectsManager();};
    Terrain(std::vector<GameObject> &objects);
    void display(const glm::mat4 &cameraView);
    void deleteBuffers();
    void ObjectsManager();


    //GETTERS

};



#endif //IMACDREAM_TERRAIN_HPP
