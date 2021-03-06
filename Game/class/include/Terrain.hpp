#ifndef IMACDREAM_TERRAIN_HPP
#define IMACDREAM_TERRAIN_HPP

#include "./GameObject.hpp"
#include <vector>
#include <map>
#include<random>
#include<chrono>
#include <functional>

class Terrain {

public:
    Terrain();
    ~Terrain()=default;
    void displayManager(const glm::mat4 &cameraView);
    void display(const int &nbCopies,const std::vector<glm::vec3> &randomPositions, const std::vector<std::string> &randomTypes, const glm::mat4 &cameraView);
    void deleteBuffers();
    void clearVectors();
    void ObjectsManager(std::vector<std::string> &names);
    void randomizeManager();
    void randomize(std::vector<glm::vec3> &randomPositions, std::vector<std::pair<glm::vec3, float>> &randomCenterRadius,
                   std::vector<std::string> &randomTypes, std::vector<std::string> &types,  const int &nbCopies,
                   std::default_random_engine &generator, std::uniform_real_distribution<float> &positionsDistrib);

    inline void setBoolValue(const int id, const bool value){ _exist[id]=value; };
    int selectedEgg(const glm::mat4 &cameraView);
    bool isSelected(const glm::mat4 &cameraView, const int i);

    inline std::vector<bool> getBool(){return _exist;};
    inline int getNbTree(){return _nbTrees;};
    inline int getNbEggs(){return _nbEggs;};
    inline int getNbMenhirs(){return _nbMenhirs;};
    inline std::vector<std::pair<glm::vec3, float>> getTreesCenters(){return _randomTreeCenterRadius;};
    std::vector<std::pair<glm::vec3, float>> getMenhirsCenters();

    void loadModels();

private:
    std::map<const std::string, GameObject> _objects;

    std::vector<glm::vec3> _modelsLoadedPositions;
    std::vector<std::pair<glm::vec3, float>> _modelsLoadedCenterRadius;
    std::vector<std::string> _modelsLoadedTypes;

    std::vector<glm::vec3> _randomTreePositions;
    std::vector<std::pair<glm::vec3, float>> _randomTreeCenterRadius;
    std::vector<std::string> _randomTreeTypes;
    int _nbTrees = 500;

    std::vector<glm::vec3> _randomMushroomsPositions;
    std::vector<std::pair<glm::vec3, float>> _randomMushroomsCenterRadius;
    std::vector<std::string> _randomMushroomsTypes;
    int _nbMushrooms = 400;

    std::vector<glm::vec3> _randomRockPositions;
    std::vector<std::pair<glm::vec3, float>> _randomRockCenterRadius;
    std::vector<std::string> _randomRockTypes;
    int _nbRocks = 500;
    int _nbMenhirs = 0 ;

    std::vector<bool> _exist;
    int _nbEggs;

    };

#endif //IMACDREAM_TERRAIN_HPP
