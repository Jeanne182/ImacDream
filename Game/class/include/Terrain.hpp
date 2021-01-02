#ifndef IMACDREAM_TERRAIN_HPP
#define IMACDREAM_TERRAIN_HPP

#include "./GameObject.hpp"
#include <vector>
#include <map>
#include<random>
#include<chrono>
#include <functional>

class Terrain {
private:
    std::map<const std::string, GameObject> _objects;
    std::vector<glm::vec3> _randomTreePositions;
    std::vector<std::string> _randomTreeTypes;
    int _nbTrees = 2000;

    std::vector<glm::vec3> _randomMushroomsPositions;
    std::vector<std::string> _randomMushroomsTypes;
    int _nbMushrooms = 1000;

    std::vector<glm::vec3> _randomRockPositions;
    std::vector<std::string> _randomRockTypes;
    int _nbRocks = 2000;

public:
    inline Terrain(){
        std::vector<std::string> objectsToImport = {
                "terrain",
                "green_pine",
                "red_pine",
                "yellow_pine",
                "mushroom",
                "mushroom_double",
                "mushroom_triple",
                "conic_rock",
                "menhir",
                "rock_circle",
                "rock_heap"
        };

        ObjectsManager(objectsToImport);
        randomizeManager();
    };
    void displayManager(const glm::mat4 &cameraView);
    void display(const int &nbCopies,const std::vector<glm::vec3> &randomPositions, const std::vector<std::string> &randomTypes, const glm::mat4 &cameraView);
    void deleteBuffers();
    void ObjectsManager(std::vector<std::string> &names);
    void randomizeManager();
    void randomize(std::vector<glm::vec3> &randomPositions, std::vector<std::string> &randomTypes,
                   std::vector<std::string> &types,  const int &nbCopies,
                   std::default_random_engine &generator, std::uniform_real_distribution<float> &positionsDistrib);
};

#endif //IMACDREAM_TERRAIN_HPP
