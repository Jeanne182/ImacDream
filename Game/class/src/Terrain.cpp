#include "../include/Terrain.hpp"
#include "../include/Utils.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>

void Terrain::displayManager(const glm::mat4 &cameraView) {
    _objects.find("terrain")->second.update(cameraView);
    display(_nbTrees, _randomTreePositions, _randomTreeTypes, cameraView);
    display(_nbMushrooms, _randomMushroomsPositions, _randomMushroomsTypes, cameraView);
    display(_nbRocks, _randomRockPositions, _randomRockTypes, cameraView);
    display(_nbEggs, _randomEggPositions, _randomEggTypes, cameraView);
}

void Terrain::display(const int &nbCopies, const std::vector<std::pair<glm::vec3, float>> &randomPositions, const std::vector<std::string> &randomTypes,
                      const glm::mat4 &cameraView){
    for (int i = 0; i < nbCopies; i++) {
        if(randomTypes==_randomEggTypes){
            if(_exist[i]){
                _objects.find(randomTypes[i])->second.setPosition(randomPositions[i].first);
                _objects.find(randomTypes[i])->second.update(cameraView);
            }
        }
        else{
            _objects.find(randomTypes[i])->second.setPosition(randomPositions[i].first);
            _objects.find(randomTypes[i])->second.update(cameraView);
        }
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
    for(uint i = 0; i < names.size(); i++){
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
    randomize(_randomTreePositions, _randomTreeCenterRadius, _randomTreeTypes, treeTypes,  _nbTrees,generator, positionsDistrib);

    //Random mushrooms color generator
    std::vector<std::string> mushroomTypes = {"mushroom", "mushroom_double", "mushroom_triple"};
    randomize(_randomMushroomsPositions, _randomMushroomsCenterRadius, _randomMushroomsTypes, mushroomTypes,  _nbMushrooms,generator, positionsDistrib);

    std::vector<std::string> rockTypes = {"conic_rock", "menhir", "rock_circle", "rock_heap"};
    randomize(_randomRockPositions, _randomRockCenterRadius, _randomRockTypes, rockTypes,  _nbRocks,generator, positionsDistrib);

    std::vector<std::string> eggTypes = {"dragon_egg"};
    randomize(_randomEggPositions, _randomEggCenterRadius, _randomEggTypes, eggTypes,  _nbEggs,generator, positionsDistrib);
    for(int i=0; i<_nbEggs; i++){
        _exist.push_back(true);
    }
}

void Terrain::randomize(std::vector<std::pair<glm::vec3, float>> &randomPositions, std::vector<std::pair<glm::vec3, float>> &randomCenterRadius,
                        std::vector<std::string> &randomTypes, std::vector<std::string> &types,  const int &nbCopies,
                        std::default_random_engine &generator, std::uniform_real_distribution<float> &positionsDistrib){

    std::uniform_int_distribution<int> typeDistrib(0,types.size() - 1);
    auto typeId = std::bind(typeDistrib, generator);

    for (int i = 0; i < nbCopies; i++){
        randomPositions.push_back(std::make_pair(glm::vec3(positionsDistrib(generator), 0.f, positionsDistrib(generator)), 1.f));
        randomTypes.push_back(types[typeId()]);
        randomCenterRadius.push_back(std::make_pair(glm::vec3(randomPositions[i].first+_objects.find(randomTypes[i])->second.getCenter()), _objects.find(randomTypes[i])->second.getHitboxRadius()));
    }

}



int Terrain::selectedEgg(const glm::mat4 &cameraView){
    for(int i=0; i<_nbEggs; i++){
        if(_exist[i]){
            if(isSelected(cameraView, i)) return i;
        }
    }
    return -1;
}


// test if the camera is pointing on an egg
bool Terrain::isSelected(const glm::mat4 &cameraView, const int i) {
    // Distance between the camera and the center of the egg
    glm::vec3 distanceVector = glm::vec3(cameraView*glm::vec4(_randomEggCenterRadius[i].first, 1.)) ;

    // Find the direction vector of the camera ray
    glm::vec3 directionVectorCam = glm::vec3(glm::vec4(0, 0, -1, 0));

    // Distance between the camera and the center of the egg projected on the camera vector
    double distanceToCenter = dotProduct(distanceVector, directionVectorCam) ;

    // Check if the ray intersect the sphere or not depending on the position of the camera
    if(distanceToCenter < 0) return false;

    // Find the closest distance between the center of the egg on the camera ray (ortho proj)
    double distanceToRay = sqrt(abs(pow(distanceToCenter, 2) - dotProduct(distanceVector, distanceVector)));

    // Check if the ray intersect the egg or not depending on the radius
    if(distanceToRay > _randomEggCenterRadius[i].second) return false ;

    return true;

}


bool Terrain::collisions(const glm::vec3 &cameraPosition){//+positions touches // si okmove sinon non
    for(int i=0; i<_nbTrees ; i++){
        if(glm::distance(cameraPosition, _randomTreeCenterRadius[i].first) < _randomTreeCenterRadius[i].second){
            std::cout << "trop proche de l'arbre" << std::endl;
            return true;
        }
    }
    //menhir
    return false;
}
