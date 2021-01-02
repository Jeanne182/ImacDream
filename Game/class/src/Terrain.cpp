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
    randomize(_randomTreePositions, _randomTreeCenterRadius, _randomTreeTypes, treeTypes,  _nbTrees,generator, positionsDistrib);

    //Random mushrooms color generator
    std::vector<std::string> mushroomTypes = {"mushroom", "mushroom_double", "mushroom_triple"};
    randomize(_randomMushroomsPositions, _randomMushroomsCenterRadius, _randomMushroomsTypes, mushroomTypes,  _nbMushrooms,generator, positionsDistrib);

    std::vector<std::string> rockTypes = {"conic_rock", "menhir", "rock_circle", "rock_heap"};
    randomize(_randomRockPositions, _randomRockCenterRadius, _randomRockTypes, rockTypes,  _nbRocks,generator, positionsDistrib);

    std::vector<std::string> eggTypes = {"dragon_egg"};
    randomize(_randomEggPositions, _randomEggCenterRadius, _randomEggTypes, eggTypes,  _nbEggs,generator, positionsDistrib);
    for(unsigned int i=0; i<_nbEggs; i++){
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
        randomCenterRadius.push_back(std::make_pair(glm::vec3(0., 0., 0.), 0.f));
        setCenter(i, randomPositions, randomCenterRadius, randomTypes);
        setHitboxRadius(i, randomPositions, randomCenterRadius, randomTypes);
    }
}



void Terrain::setCenter(const int id, std::vector<std::pair<glm::vec3, float>> &randomPosition,
                        std::vector<std::pair<glm::vec3, float>> &randomCenterRadius,
                        std::vector<std::string> &randomTypes){
    glm::vec3 max = findMax(id, randomPosition, randomTypes);
    glm::vec3 min = findMin(id, randomPosition, randomTypes);
    randomCenterRadius.at(id).first=((max+min)/glm::vec3(2., 2., 2.));
}



void Terrain::setHitboxRadius(const int id, std::vector<std::pair<glm::vec3, float>> &randomPosition,
                              std::vector<std::pair<glm::vec3, float>> &randomCenterRadius, std::vector<std::string> &randomTypes){
    float radius ;
    for(auto meshes : _objects.find(randomTypes[id])->second.getModel()->_meshes){
        for(auto vertices : meshes._vertices){
            glm::vec3 vertex = glm::vec3(vertices.position*randomPosition[id].second+randomPosition[id].first);
            radius = float(glm::distance(vertex, randomCenterRadius[id].first));
            if(radius > randomCenterRadius[id].second ) {
                randomCenterRadius[id].second = radius;
            }
        }
    }
}



glm::vec3 Terrain::findMax(const int id, std::vector<std::pair<glm::vec3, float>> &randomPosition, std::vector<std::string> &randomTypes){
    glm::vec3 max = randomPosition[id].first;
    for(auto meshes : _objects.find(randomTypes[id])->second.getModel()->_meshes){
        for(auto vertices : meshes._vertices){
            glm::vec3 vertex = glm::vec3(vertices.position * randomPosition[id].second + randomPosition[id].first);
            if(vertex.x> max.x) max.x = vertex.x;
            if(vertex.y > max.y) max.y = vertex.y;
            if(vertex.z > max.z) max.z = vertex.z;
        }
    }
    return max;
}

glm::vec3 Terrain::findMin(const int id, std::vector<std::pair<glm::vec3, float>> &randomPosition, std::vector<std::string> &randomTypes){
    glm::vec3 min =  randomPosition[id].first;
    for(auto meshes : _objects.find(randomTypes[id])->second.getModel()->_meshes){
        for(auto vertices : meshes._vertices){
            glm::vec3 vertex = glm::vec3(vertices.position* randomPosition[id].second+ randomPosition[id].first);
            if(vertex.x< min.x) min.x = vertex.x;
            if(vertex.y < min.y) min.y = vertex.y;
            if(vertex.z < min.z) min.z = vertex.z;
        }
    }
    return min;
}





int Terrain::selectedEgg(const glm::mat4 &cameraView, const glm::vec3 &cameraPosition){
    for(unsigned int i=0; i<_nbEggs; i++){
        if(_exist[i]==true){
            if(isSelected(cameraView, cameraPosition, i)) return i;
        }
    }
    return -1;
}


// test if the camera is pointing on an object
bool Terrain::isSelected(const glm::mat4 &cameraView, const glm::vec3 &cameraPosition, const int i) {
    // Distance between the camera and the center of the interactive object
    glm::vec3 distanceVector = glm::vec3(cameraView*glm::vec4(_randomEggCenterRadius[i].first, 1.)) ;

    // Find the direction vector of the camera ray
    glm::vec3 directionVectorCam = glm::vec3(glm::vec4(0, 0, -1, 0));

    // Distance between the camera and the center of the interactive object projected on the camera vector
    double distanceToCenter = dotProduct(distanceVector, directionVectorCam) ;

    // Check if the ray intersect the sphere or not depending on the position of the camera
    if(distanceToCenter < 0) return false;

    // Find the closest distance between the center of the object on the camera ray (ortho proj)
    double distanceToRay = sqrt(abs(pow(distanceToCenter, 2) - dotProduct(distanceVector, distanceVector)));

    // Check if the ray intersect the sphere or not depending on the radius
    if(distanceToRay > _randomEggCenterRadius[i].second) return false ;

    return true;

}





