#include "../include/InteractiveObjectManager.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>


void InteractiveObjectManager::display(const glm::mat4 &cameraView) {/*
    _objectsToFind[0].setPosition(glm::vec3(1.f, 1.f, 1.f));

    _objectsToFind[0].setScale(0.1f);
    _objectsToFind[0].setCenter();

    _objectsToFind[0].setHitboxRadius();
    std::cout << "position tree : " << _objectsToFind[0].getPosition() << std::endl;
    std::cout << "center tree : " << _objectsToFind[0].getCenter() << std::endl;
    std::cout << "radius tree : " << _objectsToFind[0].getHitboxRadius() << std::endl;

    _objectsToFind[0].update(cameraView);

    _objectsToFind[1].setPosition(_objectsToFind[0].getCenter());
    _objectsToFind[1].setScale(_objectsToFind[0].getHitboxRadius());
    _objectsToFind[1].setCenter();

    _objectsToFind[1].setHitboxRadius();
    std::cout << "position sphere : " << _objectsToFind[1].getPosition() << std::endl;
    std::cout << "center sphere : " << _objectsToFind[1].getCenter() << std::endl;
    std::cout << "radius sphere : " << _objectsToFind[1].getHitboxRadius() << std::endl;
    _objectsToFind[1].update(cameraView);*/

    _objectsToFind[0].setPosition(glm::vec3(3.f, -9.f, 8.f));

    //_objectsToFind[0].setScale(0.1f);
    _objectsToFind[0].setCenter();
    _objectsToFind[0].setHitboxRadius();
    _objectsToFind[0].update(cameraView);

    _objectsToFind[1].setPosition(_objectsToFind[0].getCenter());
    _objectsToFind[1].setScale(_objectsToFind[0].getHitboxRadius());
    _objectsToFind[1].setCenter();

    _objectsToFind[1].setHitboxRadius();
    _objectsToFind[1].update(cameraView);

}

void InteractiveObjectManager::deleteBuffers() {
    for(auto & _objectsToFind : _objectsToFind){
        _objectsToFind.deleteBuffers();
    }
}

void InteractiveObjectManager::InteractiveObjectsManager() {
    auto* InteractiveObjects = new std::vector<InteractiveObject>;
    std::string modelsPath = AssetManager::Get()->appPath().dirPath() + "Assets/models";

    //SPHERE
    Sphere sphere(1,32,32);
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    Material material;
    material.Ka = glm::vec4(1.f,1.f,1.f,1.f);
    material.Kd = glm::vec4(1.f,0.f,0.5f,1.f);
    material.Ks = glm::vec4(0.5f,0.5f,0.5f,0.5f);
    std::vector<ShapeVertex> meshVertices;
    for (GLint i = 0; i < sphere.getVertexCount();i++){
        indices.push_back(i);
        meshVertices.push_back(sphere.getDataPointer()[i]);
    }
    Mesh* sphereMesh = new Mesh(meshVertices, indices, textures, material);
    Model* sphereModel = new Model();
    sphereModel->_meshes.push_back(*sphereMesh);
    InteractiveObject sphereObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *sphereModel, 0, glm::vec3(0, 0, 0), 0);
    InteractiveObjects->push_back(sphereObject);

    //DRAGON EGG
    std::string pathModelTree = modelsPath + "/dragon_egg.obj";
    auto* egg = new Model(pathModelTree);
    InteractiveObject eggObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *egg, 0, glm::vec3(0, 0, 0), 2);
    InteractiveObjects->push_back(eggObject);


    _objectsToFind = *InteractiveObjects;
}



