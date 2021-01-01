#include<iostream>
#include "../include/Terrain.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>

void Terrain::setMapTerrain() {
    glm::vec3 minVector;
    for(auto meshes : _objects[TERRAIN]._model->_meshes){
        for(auto vertices : meshes._vertices){
            _mapTerrain[std::make_tuple(vertices.position.x*100, vertices.position.z*100)] = vertices.position.y;
        }
    }
}

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
void Terrain::display(const glm::mat4 &cameraView) {
    //setMapTerrain();
    _objects[TREE].setPosition(glm::vec3(5.f, 0.f, -5.f));
    _objects[TREE].setCenter();
    _objects[TREE].setHitboxRadius();
    _objects[TREE].update(cameraView);

    _objects[TREE].setPosition(glm::vec3(-10.f, 0.f, -5.f));
    _objects[TREE].setCenter();
    _objects[TREE].setHitboxRadius();
    _objects[TREE].update(cameraView);

    _objects[TERRAIN].update(cameraView);

}

void Terrain::deleteBuffers() {
    for(auto & _object : _objects){
        _object.deleteBuffers();
        delete &_object;
    }
    delete &_objects;
    _objects.clear();
}

void Terrain::ObjectsManager() {
    auto* objects = new std::vector<GameObject>;
    std::string modelsPath = AssetManager::Get()->appPath().dirPath() + "Assets/models";

    //TREE
    std::string pathModelTree = modelsPath + "/green_pine.obj";
    auto* tree = new Model(pathModelTree);
    GameObject treeObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *tree, 0, glm::vec3(0, 0, 0));
    objects->push_back(treeObject);

    _objectsDisplayed.insert(std::make_pair("tree", &treeObject));

    //TERRAIN
    Model* terrain = new Model(modelsPath + "/terrain.obj");
    GameObject terrainObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *terrain, 0, glm::vec3(0, 0, 0));
    objects->push_back(terrainObject);
    _objectsDisplayed.insert(std::make_pair("terrain", &terrainObject));
    _objects = *objects;
}
