#include "../include/Terrain.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>
#include<random>
#include<chrono>
#include <functional>


void Terrain::display(const glm::mat4 &cameraView) {
    _objects.find("terrain")->second.update(cameraView);

    for (int i = 0; i < _nbTrees; i++) {
        _objects.find(_randomTreeTypes[i])->second.setPosition(_randomTreePositions[i]);
        _objects.find(_randomTreeTypes[i])->second.setCenter();
        _objects.find(_randomTreeTypes[i])->second.setHitboxRadius();
        _objects.find(_randomTreeTypes[i])->second.update(cameraView);
    }

    for (int i = 0; i < _nbMushrooms; i++) {
        _objects.find(_randomMushroomsTypes[i])->second.setPosition(_randomMushroomsPositions[i]);
        _objects.find(_randomMushroomsTypes[i])->second.setCenter();
        _objects.find(_randomMushroomsTypes[i])->second.setHitboxRadius();
        _objects.find(_randomMushroomsTypes[i])->second.update(cameraView);
    }
}

void Terrain::deleteBuffers() {
    std::map<const std::string, GameObject>::iterator it;
    for(it = _objects.begin(); it != _objects.end(); it++){
        it->second.deleteBuffers();;
    }
    delete &_objects;
    _objects.clear();
}

void Terrain::ObjectsManager() {
    //Terrain
    GameObject terrainObject("/terrain.obj");
    _objects.insert(std::make_pair("terrain", terrainObject));

    //Green pine
    GameObject treeObject("/green_pine.obj");
    _objects.insert(std::make_pair("tree", treeObject));

    //Red pine
    GameObject orangeTreeObject("/red_pine.obj");
    _objects.insert(std::make_pair("orangeTree", orangeTreeObject));

    //Yellow pine
    GameObject yellowTreeObject("/yellow_pine.obj");
    _objects.insert(std::make_pair("yellowTree", orangeTreeObject));

    //Mushroom
    GameObject mushroomObject("/mushroom1.obj");
    _objects.insert(std::make_pair("mushroom", mushroomObject));

    //Mushroom double
    GameObject mushroomDoubleObject("/mushroom_double.obj");
    _objects.insert(std::make_pair("mushroom_double", mushroomDoubleObject));

    //Mushroom triple
    GameObject mushroomTripleObject("/mushroom_triple.obj");
    _objects.insert(std::make_pair("mushroom_triple", mushroomTripleObject));
}

void Terrain::randomize() {
    //Seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    //Random tree positions generator
    std::uniform_real_distribution<float> treePositionsDistrib(-500,500);

    //Random tree color generator
    std::uniform_int_distribution<int> TreeTypeDistrib(0,2);
    auto treeTypeId = std::bind(TreeTypeDistrib, generator);
    std::vector<std::string> treeTypes = {"tree", "yellowTree", "orangeTree"};

    for (int i = 0; i < _nbTrees; i++){
        _randomTreePositions.push_back(glm::vec3(treePositionsDistrib(generator), 0.f, treePositionsDistrib(generator)));
        _randomTreeTypes.push_back(treeTypes[treeTypeId()]);
    }

    //Random mushrooms positions generator
    std::uniform_real_distribution<float> mushroomPositionsDistrib(-500,500);

    //Random mushrooms color generator
    std::uniform_int_distribution<int> mushroomTypeDistrib(0,2);
    auto mushroomTypeId = std::bind(mushroomTypeDistrib, generator);
    std::vector<std::string> mushroomTypes = {"mushroom", "mushroom_double", "mushroom_triple"};

    for (int i = 0; i < _nbTrees; i++){
        _randomMushroomsPositions.push_back(glm::vec3(mushroomPositionsDistrib(generator), 0.f, mushroomPositionsDistrib(generator)));
        _randomMushroomsTypes.push_back(mushroomTypes[mushroomTypeId()]);
    }
}
