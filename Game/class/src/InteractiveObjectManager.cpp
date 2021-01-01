#include "../include/InteractiveObjectManager.hpp"
#include "../include/AssetsManager.hpp"
#include <glimac/Sphere.hpp>
#include <map>


void InteractiveObjectManager::display(const glm::mat4 &cameraView) {

    //InteractiveObject *dragonegg1 = _objectsToFind.find(0)->second;

    _objectsToFind.setPosition(glm::vec3(3.f, -10.f, -8.f));
    _objectsToFind.setCenter();
    _objectsToFind.setHitboxRadius();
    _objectsToFind.update(cameraView);

    _objectsToFind.setPosition(glm::vec3(5.f, -10.f, -8.f));
    _objectsToFind.setCenter();
    _objectsToFind.setHitboxRadius();
    _objectsToFind.update(cameraView);


}

void InteractiveObjectManager::deleteBuffers() {


}

InteractiveObjectManager::InteractiveObjectManager():_objectsToFind(){
    //auto* InteractiveObjects = new std::map<int, InteractiveObject*>;

    for(unsigned int i=0; i<nbObjects ; i++){
        _exist[i]=true;
    }


    //DRAGON EGG
    auto* egg = new Model(AssetManager::Get()->modelFile("dragon_egg"));
    InteractiveObject eggObject(glm::vec3(0.f,0.f,0.f), 1.f, glm::vec3(0.f, 0.f, 0.f), *egg, 0, glm::vec3(0, 0, 0), 0);
    //InteractiveObjects->insert(std::make_pair(eggObject.getID(), &eggObject));


    _objectsToFind = eggObject;
}



