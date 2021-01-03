#include "../include/Terrain.hpp"
#include "../include/Utils.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>
#include <cstdio>

Terrain::Terrain(){
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
            "dragon_egg",
            "orange_egg",
            "green_egg"
    };

    ObjectsManager(objectsToImport);
    randomizeManager();

    loadModels();
    _nbEggs = _modelsLoadedPositions.size();
    for(int i=0; i<_nbEggs; i++){
        _exist.push_back(true);
    }
}


void Terrain::displayManager(const glm::mat4 &cameraView) {
    _objects.find("terrain")->second.update(cameraView);
    display(_nbTrees, _randomTreePositions, _randomTreeTypes, cameraView);
    display(_nbMushrooms, _randomMushroomsPositions, _randomMushroomsTypes, cameraView);
    display(_nbRocks, _randomRockPositions, _randomRockTypes, cameraView);
    display(_modelsLoadedPositions.size(), _modelsLoadedPositions, _modelsLoadedTypes, cameraView);
}

void Terrain::display(const int &nbCopies, const std::vector<glm::vec3> &randomPositions, const std::vector<std::string> &randomTypes,
                      const glm::mat4 &cameraView){
    for (int i = 0; i < nbCopies; i++) {
        if(randomTypes==_modelsLoadedTypes){
            if(_exist[i]){
                _objects.find(randomTypes[i])->second.setPosition(randomPositions[i]);
                _objects.find(randomTypes[i])->second.update(cameraView);
            }
        }
        else{
            _objects.find(randomTypes[i])->second.setPosition(randomPositions[i]);
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
    for(auto & name : names){
        std::string path = "/" + name + ".obj";
        GameObject object(path);
        _objects.insert(std::make_pair(name, object));


    }
}

void Terrain::loadModels() {
    std::ifstream is(AssetManager::Get()->txtFile("modelsLoader.txt"));

    char xPos[10], yPos[10], zPos[10];
    glm::vec3 pos;
    char type[50], path[50];
    for (std::string str; std::getline(is, str);) {
        if(!str.empty()){
            char c[str.size() + 1];
            strcpy(c, str.c_str());
            sscanf((const char *)c, "%s", type);
            if (std::strcmp ("model", type) == 0){
                sscanf((const char *)c, "%s %s", type, path);
                _modelsLoadedTypes.emplace_back(path);
            }
            else if (std::strcmp ("pos", type) == 0) {
                sscanf((const char *) c, "%s %s %s %s", type, xPos, yPos, zPos);
                pos = glm::vec3(std::stof(xPos), std::stof(yPos), std::stof(zPos));
                _modelsLoadedPositions.emplace_back(pos);
                _modelsLoadedCenterRadius.emplace_back(glm::vec3(pos + _objects.find(path)->second.getCenter()),_objects.find(path)->second.getHitboxRadius());
            }
        }
    }
    std::cout<<"{"; //TO DELETE
    for(int j = 0; j<_modelsLoadedPositions.size(); j++){
        std::cout<<"glm::vec3("<<_modelsLoadedPositions[j][0]<<","<<_modelsLoadedPositions[j][1]<<","<<_modelsLoadedPositions[j][2]<<"), ";
    }
    std::cout<<std::endl;
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
}

void Terrain::randomize(std::vector<glm::vec3> &randomPositions, std::vector<std::pair<glm::vec3, float>> &randomCenterRadius,
                        std::vector<std::string> &randomTypes, std::vector<std::string> &types,  const int &nbCopies,
                        std::default_random_engine &generator, std::uniform_real_distribution<float> &positionsDistrib){

    std::uniform_int_distribution<int> typeDistrib(0,types.size() - 1);
    auto typeId = std::bind(typeDistrib, generator);

    for (int i = 0; i < nbCopies; i++){
        randomPositions.emplace_back(positionsDistrib(generator), -2.5f, positionsDistrib(generator));
        randomTypes.push_back(types[typeId()]);
        if(types[typeId()]=="menhir") _nbMenhirs++;
        randomCenterRadius.emplace_back(glm::vec3(randomPositions[i]+_objects.find(randomTypes[i])->second.getCenter()), _objects.find(randomTypes[i])->second.getHitboxRadius());
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
    glm::vec3 distanceVector = glm::vec3(cameraView*glm::vec4(_modelsLoadedCenterRadius[i].first, 1.)) ;

    // Find the direction vector of the camera ray
    glm::vec3 directionVectorCam = glm::vec3(glm::vec4(0, 0, -1, 0));

    // Distance between the camera and the center of the egg projected on the camera vector
    double distanceToCenter = dotProduct(distanceVector, directionVectorCam) ;

    // Check if the ray intersect the sphere or not depending on the position of the camera
    if(distanceToCenter < 0) return false;

    // Find the closest distance between the center of the egg on the camera ray (ortho proj)
    double distanceToRay = sqrt(abs(pow(distanceToCenter, 2) - dotProduct(distanceVector, distanceVector)));

    // Check if the ray intersect the egg or not depending on the radius
    if(distanceToRay > _modelsLoadedCenterRadius[i].second) return false ;

    return true;

}


std::vector<std::pair<glm::vec3, float>> Terrain::getMenhirsCenters(){
    std::vector<std::pair<glm::vec3, float>> menhirsCenters;
    for(int i=0 ; i<_nbRocks; i++){
        if(_randomRockTypes[i]=="menhir"){
            menhirsCenters.push_back(_randomRockCenterRadius[i]);
        }
    }
    return menhirsCenters;
}


void Terrain::clearVectors(){
    for(int i=0; i<_modelsLoadedPositions.size(); i++){
        _modelsLoadedPositions.clear();
        _modelsLoadedCenterRadius.clear();
        _modelsLoadedTypes.clear();
    }
    for(int i=0; i<_nbTrees; i++){
        _randomTreePositions.clear();
        _randomTreeCenterRadius.clear();
        _randomTreeTypes.clear();
    }
    for(int i=0; i<_nbMushrooms; i++){
        _randomMushroomsPositions.clear();
        _randomMushroomsCenterRadius.clear();
        _randomMushroomsTypes.clear();
    }
    for(int i=0; i<_nbRocks; i++){
        _randomRockPositions.clear();
        _randomRockCenterRadius.clear();
        _randomRockTypes.clear();
    }
    _nbMenhirs=0;
}