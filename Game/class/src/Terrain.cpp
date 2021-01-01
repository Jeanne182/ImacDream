#include<iostream>
#include "../include/Terrain.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>


void Terrain::display(const glm::mat4 &cameraView) {
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
