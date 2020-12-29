#ifndef IMACDREAM_TERRAIN_HPP
#define IMACDREAM_TERRAIN_HPP

#include "./GameObject.hpp"
#include <vector>
#include <map>

enum TerrainObjects{
    SPHERE,
    TREE,
    TRUNK,
    RUNE,
    HUT,
    TERRAIN
};

class Terrain {
private:
//    std::vector<GameObject> _objects;
    std::vector<GameObject> _objectsDisplayed;
    std::map<std::tuple<int, int>, float> _mapTerrain;

public:
    std::vector<GameObject> _objects;//PRIVATE

    inline Terrain(){ ObjectsManager();};
    Terrain(std::vector<GameObject> &objects);
    void display(const glm::mat4 &cameraView);
    void deleteBuffers();
    void ObjectsManager();
    void setMapTerrain();
    float getTerrainHeight(const float x, const float z);




    //GETTERS

};



#endif //IMACDREAM_TERRAIN_HPP
