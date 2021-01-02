#ifndef IMACDREAM_TERRAIN_HPP
#define IMACDREAM_TERRAIN_HPP

#include "./GameObject.hpp"
#include <vector>
#include <map>

class Terrain {
private:
    std::map<const std::string, GameObject> _objects;
    std::vector<glm::vec3> _randomTreePositions;
    std::vector<std::string> _randomTreeTypes;
    int _nbTrees = 1000;

    std::vector<glm::vec3> _randomMushroomsPositions;
    std::vector<std::string> _randomMushroomsTypes;
    int _nbMushrooms = 400;

public:
    inline Terrain(){ ObjectsManager();
    randomize();};
    Terrain(std::vector<GameObject> &objects);
    void display(const glm::mat4 &cameraView);
    void deleteBuffers();
    void ObjectsManager();
    void randomize();
};



#endif //IMACDREAM_TERRAIN_HPP
