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

    std::vector<glm::vec3> _modelsLoadedPositions;
    std::vector<std::pair<glm::vec3, float>> _modelsLoadedCenterRadius;
    std::vector<std::string> _modelsLoadedTypes;

    std::vector<glm::vec3> _randomTreePositions;
    std::vector<std::pair<glm::vec3, float>> _randomTreeCenterRadius;
    std::vector<std::string> _randomTreeTypes;
    int _nbTrees = 200;

    std::vector<glm::vec3> _randomMushroomsPositions;
    std::vector<std::pair<glm::vec3, float>> _randomMushroomsCenterRadius;
    std::vector<std::string> _randomMushroomsTypes;
    int _nbMushrooms = 200;

    std::vector<glm::vec3> _randomRockPositions;
    std::vector<std::pair<glm::vec3, float>> _randomRockCenterRadius;
    std::vector<std::string> _randomRockTypes;
    int _nbRocks = 200;
    int _nbMenhirs = 0 ;

    std::vector<glm::vec3> _randomEggPositions;
    std::vector<std::pair<glm::vec3, float>> _randomEggCenterRadius;
    std::vector<std::string> _randomEggTypes;
    std::vector<bool> _exist;
    int _nbEggs = 200;

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
    void display(const int &nbCopies,const std::vector<glm::vec3> &randomPositions, const std::vector<std::string> &randomTypes, const glm::mat4 &cameraView);
    void deleteBuffers();
    void ObjectsManager(std::vector<std::string> &names);
    void randomizeManager();
    void randomize(std::vector<glm::vec3> &randomPositions, std::vector<std::pair<glm::vec3, float>> &randomCenterRadius,
                   std::vector<std::string> &randomTypes, std::vector<std::string> &types,  const int &nbCopies,
                   std::default_random_engine &generator, std::uniform_real_distribution<float> &positionsDistrib);

    inline void setBoolValue(const int id){ _exist[id]=false; };
    int selectedEgg(const glm::mat4 &cameraView);
    bool isSelected(const glm::mat4 &cameraView, const int i);
    //bool collisions(const glm::vec3 &cameraPosition);

    inline std::vector<bool> getBool(){return _exist;};
    inline int getNbTree(){return _nbTrees;};
    inline int getNbMenhirs(){return _nbMenhirs;};
    inline std::vector<std::pair<glm::vec3, float>> getTreesCenters(){return _randomTreeCenterRadius;};
    std::vector<std::pair<glm::vec3, float>> getMenhirsCenters();

    void loadModels();

    };

#endif //IMACDREAM_TERRAIN_HPP
