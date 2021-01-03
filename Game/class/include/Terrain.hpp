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

    std::vector<std::pair<glm::vec3, float>> _randomTreePositions;
    std::vector<std::pair<glm::vec3, float>> _randomTreeCenterRadius;
    std::vector<std::string> _randomTreeTypes;
    int _nbTrees = 20;

    std::vector<std::pair<glm::vec3, float>> _randomMushroomsPositions;
    std::vector<std::pair<glm::vec3, float>> _randomMushroomsCenterRadius;
    std::vector<std::string> _randomMushroomsTypes;
    int _nbMushrooms = 20;

    std::vector<std::pair<glm::vec3, float>> _randomRockPositions;
    std::vector<std::pair<glm::vec3, float>> _randomRockCenterRadius;
    std::vector<std::string> _randomRockTypes;
    int _nbRocks = 20;

    std::vector<std::pair<glm::vec3, float>> _randomEggPositions;
    std::vector<std::pair<glm::vec3, float>> _randomEggCenterRadius;
    std::vector<std::string> _randomEggTypes;
    std::vector<bool> _exist;
    int _nbEggs = 50;

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
                "rock_heap",
                "dragon_egg"
        };

        ObjectsManager(objectsToImport);
        randomizeManager();
    };
    ~Terrain()=default;
    void displayManager(const glm::mat4 &cameraView);
    void display(const int &nbCopies,const std::vector<std::pair<glm::vec3, float>> &randomPositions, const std::vector<std::string> &randomTypes, const glm::mat4 &cameraView);
    void deleteBuffers();
    void ObjectsManager(std::vector<std::string> &names);
    void randomizeManager();
    void randomize(std::vector<std::pair<glm::vec3, float>> &randomPositions, std::vector<std::pair<glm::vec3, float>> &randomCenterRadius,
                   std::vector<std::string> &randomTypes, std::vector<std::string> &types,  const int &nbCopies,
                   std::default_random_engine &generator, std::uniform_real_distribution<float> &positionsDistrib);

    inline void setBoolValue(const int id){ _exist[id]=false; };
    int selectedEgg(const glm::mat4 &cameraView);
    bool isSelected(const glm::mat4 &cameraView, const int i);
    bool collisions(const glm::vec3 &cameraPosition);

    inline std::vector<bool> getBool(){return _exist;};

    };

#endif //IMACDREAM_TERRAIN_HPP
