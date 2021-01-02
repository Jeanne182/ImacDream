#include "../include/Terrain.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>

void Terrain::displayManager(const glm::mat4 &cameraView) {
    _objects.find("terrain")->second.update(cameraView);
    display(_nbTrees, _randomTreePositions, _randomTreeTypes, cameraView);
    display(_nbMushrooms, _randomMushroomsPositions, _randomMushroomsTypes, cameraView);
    display(_nbRocks, _randomRockPositions, _randomRockTypes, cameraView);
    display(_nbEggs, _randomEggPositions, _randomEggTypes, cameraView);
}

void Terrain::display(const int &nbCopies, const std::vector<glm::vec3> &randomPositions, const std::vector<std::string> &randomTypes,
                      const glm::mat4 &cameraView){
    for (int i = 0; i < nbCopies; i++) {
        _objects.find(randomTypes[i])->second.setPosition(randomPositions[i]);
        _objects.find(randomTypes[i])->second.setCenter();
        _objects.find(randomTypes[i])->second.setHitboxRadius();
        _objects.find(randomTypes[i])->second.update(cameraView);
    }
}

void Terrain::deleteBuffers() {
    std::map<const std::string, GameObject>::iterator it;
    for(it = _objects.begin(); it != _objects.end(); it++){
        it->second.deleteBuffers();
    }
    _objects.clear();
}

void Terrain::ObjectsManager(std::vector<std::string> &names) {
    for(int i = 0; i < names.size(); i++){
        std::string path = "/" + names[i] + ".obj";
        GameObject object(path);
        _objects.insert(std::make_pair(names[i], object));
    }
}

void Terrain::randomizeManager() {
    //Seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    //Random positions generator
    std::uniform_real_distribution<float> positionsDistrib(-500,500);

    std::vector<std::string> treeTypes = {"green_pine", "yellow_pine", "red_pine"};
    randomize(_randomTreePositions, _randomTreeTypes,treeTypes,  _nbTrees,generator, positionsDistrib);

    //Random mushrooms color generator
    std::vector<std::string> mushroomTypes = {"mushroom", "mushroom_double", "mushroom_triple"};
    randomize(_randomMushroomsPositions, _randomMushroomsTypes,mushroomTypes,  _nbMushrooms,generator, positionsDistrib);

    std::vector<std::string> rockTypes = {"conic_rock", "menhir", "rock_circle", "rock_heap"};
    randomize(_randomRockPositions, _randomRockTypes,rockTypes,  _nbRocks,generator, positionsDistrib);

    std::vector<std::string> eggTypes = {"dragon_egg"};
    randomize(_randomEggPositions, _randomEggTypes,eggTypes,  _nbEggs,generator, positionsDistrib);

}

void Terrain::randomize(std::vector<glm::vec3> &randomPositions, std::vector<std::string> &randomTypes,
                    std::vector<std::string> &types,  const int &nbCopies,
                    std::default_random_engine &generator, std::uniform_real_distribution<float> &positionsDistrib){

    std::uniform_int_distribution<int> typeDistrib(0,types.size() - 1);
    auto typeId = std::bind(typeDistrib, generator);

    for (int i = 0; i < nbCopies; i++){
        randomPositions.emplace_back(positionsDistrib(generator), 0.f, positionsDistrib(generator));
        randomTypes.push_back(types[typeId()]);
    }
}


//void Terrain::setMapTerrain() {
//    glm::vec3 minVector;
//    for(auto meshes : _objects[TERRAIN]._model->_meshes){
//        for(auto vertices : meshes._vertices){
//            _mapTerrain[std::make_tuple(vertices.position.x*100, vertices.position.z*100)] = vertices.position.y;
//        }
//    }
//}

/*
float Terrain::getTerrainHeight(const float x, const float z){
    std::map<std::tuple<int, int>, float>::iterator low, prev;
    std::tuple<int, int> pos = std::tuple<int, int>(x*100, z*100);
    low = _mapTerrain.lower_bound(pos);
    if (low == _mapTerrain.end()) {
        std::cout << "Position not find" << std::endl;
    }
    else if (low == _mapTerrain.begin()) {
        std::cout << "low= " << std::get<0>(low->first) << " & " << std::get<1>(low->first) << std::endl;
        return low->second;
    }
    else {
        prev = std::prev(low);
        if ((std::get<0>(pos) - std::get<0>(prev->first) && std::get<1>(pos) - std::get<1>(prev->first)) < (std::get<0>(low->first) - std::get<0>(pos) && std::get<1>(low->first) - std::get<1>(pos))){
            std::cout << "prev= " << std::get<0>(prev->first)/100 << " & " << std::get<1>(prev->first)/100 << std::endl;
            std::cout << "y= " << prev->second << std::endl;
            return prev->second;
        }

        else{
            std::cout << "low= " << std::get<0>(low->first)/100 << " & " << std::get<1>(low->first)/100 << std::endl;
            std::cout << "y= " << low->second << std::endl;
            return low->second;
        }
    }
    return 5.f;
}
*/